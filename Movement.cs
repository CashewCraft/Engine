using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour {

	Rigidbody2D rb;

	public float SpeedLimit = 8;
	public float Acceleration = 2f;
	public float Deceleration = 0.5f; //0.05f;
	public float Manuvarbility = 3f;
	public float Rot = 3f;

	public float MinSpeed = 3;

	public float BoostDelay = 2f;
	float BoostTimer = 0f;

	//Vector2 Thrust;
	public TargetTracker TargetBeam;

	void Start()
	{
		rb = transform.GetComponent<Rigidbody2D>();
    }
	
	void Update ()
	{
		if (BoostTimer > 0) { BoostTimer -= Time.deltaTime; }

		Vector2 MousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		Vector2 MyPos = transform.position;
		float angleRad = Mathf.Atan2(MyPos.y - MousePos.y, MyPos.x - MousePos.x);
		
		transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.AngleAxis((angleRad * Mathf.Rad2Deg)+90, Vector3.forward), Rot * Time.deltaTime);

		if (Input.GetButton("Accelerate"))
		{
			//Thrust=(transform.up*SpeedLimit);

			if (rb.velocity.magnitude < MinSpeed && rb.velocity.normalized != (Vector2)transform.up)
			{
				rb.AddForce(transform.up * Acceleration * MinSpeed);
				//rb.velocity = transform.up * Acceleration * MinSpeed;
			}
			else
			{
				rb.AddForce(transform.up * Acceleration);
			}

			if (Input.GetButtonDown("Left"))
			{
				//Velocity += (Vector2)(-transform.right * Manuvarbility);
				rb.AddForce(-transform.right * Manuvarbility, ForceMode2D.Impulse);
			}
			if (Input.GetButtonDown("Right"))
			{
				//Velocity += (Vector2)(transform.right * Manuvarbility);
				rb.AddForce(transform.right * Manuvarbility, ForceMode2D.Impulse);
			}
		}
		else if (Input.GetButton("Decelerate"))
		{
			//Thrust -= Thrust * Deceleration;
			rb.AddForce(-rb.velocity*Deceleration);
		}
		else if (Input.GetButtonDown("Boost") && BoostTimer <= 0)
		{
			rb.velocity = transform.up * SpeedLimit;
			print(rb.velocity.magnitude);
		}

		if (Input.GetButtonDown("Target"))
		{
			if (TargetBeam.GetTarget() != null)
			{
				if (transform.GetComponent<Gun>().Crosshair.Target != null)
				{
					transform.GetComponent<Gun>().Crosshair.Target.transform.GetChild(1).GetComponent<SpriteRenderer>().enabled = false;
				}
				transform.GetComponent<Gun>().Crosshair.Target = TargetBeam.GetTarget().GetComponent<Rigidbody2D>();
				transform.GetComponent<Gun>().Crosshair.Target.transform.GetChild(1).GetComponent<SpriteRenderer>().enabled = true;
			}
		}

		//rb.velocity = (Velocity == new Vector2())?rb.velocity*Deceleration:Velocity;
		rb.velocity = Vector2.ClampMagnitude(rb.velocity, SpeedLimit);

		transform.GetComponent<Gun>().Firing = Input.GetButton("Fire");
	}

	void FixedUpdate()
	{
		Vector2 BL = Camera.main.ScreenToWorldPoint(new Vector3(0, 0, 20));
		Vector2 TR = Camera.main.ScreenToWorldPoint(new Vector3(Camera.main.pixelWidth, Camera.main.pixelHeight, 20));
		if (transform.position.x < BL.x || transform.position.x > TR.x)
		{
			rb.velocity = new Vector2(rb.velocity.x * -1, rb.velocity.y);

			transform.position = new Vector2((transform.position.x < BL.x) ? BL.x : TR.x, transform.position.y);
		}
		if (transform.position.y < BL.y || transform.position.y > TR.y)
		{
			rb.velocity = new Vector2(rb.velocity.x, rb.velocity.y * -1);

			transform.position = new Vector2(transform.position.x, (transform.position.y < BL.y) ? BL.y : TR.y);
		}
	}
}

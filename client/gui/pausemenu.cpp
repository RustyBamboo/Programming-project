using System.Collections;

public class PauseMenu : MonoBehaviour {

	// Link the Panel that you want this to work w/ 
	public GameObject PauseUI;

	private bool paused = false;

	void Start() {

		//when the game is initialized the pause menu will not be visable
		PauseUI.SetActive(false);

	}

	void Update() {

		if (Input.GetButtonDown("Pause"))
		{
			paused = !paused;
		}

		if (paused)
		{
			// If the pause menu is up, time scale is set to 0 (halts all movement)
			PauseUI.SetActive(true);
			Time.timeScale = 0;
		}
		if (!paused)
		{
			// If the pause menu is down, everything will run as expected 
			PauseUI.SetActive(false);
			Time.timeScale = 1;
		}
	}

	public void Resume() {
		paused = false;
	}

	public void Restart() {
		Application.LoadLevel(Application.loadedLevel);
	}

	public void MainMenu() {
		Application.LoadLevel("mainMenu");
	}

	public void Quit() {
		Application.Quit();
	}
}

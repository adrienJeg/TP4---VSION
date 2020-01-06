#include <opencv2\core\core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <string>
#include <iostream>
#include <aruco.h>

#define ESC_KEY 27
#define Q_KEY 113


using namespace std;
using namespace cv;
using namespace aruco;

// Declaring a VideoCapture object
// it can open a camera feed
VideoCapture cap;
Mat image;

// A key that we use to store the user keyboard input
char key;

// Creating a window to display the images
string windowName = "ArUco";

int num = 0;

// Main Method
int main(int argc, char * argv[])
{
	// creation d’un detecteur de marqueurs
	MarkerDetector myDetector;
	// liste de marqueurs : sera remplie par ArUco
	vector<Marker> markers;
	

	cap.open(num);

	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	
	while ((key != ESC_KEY) && (key!= Q_KEY)) 
	{
		// Getting the new image from the camera
		cap.read(image);

		// On appelle la fonction qui gère la détection des coins et leur affichage
		if (image.size > 0)
		{
			// detection
			myDetector.detect(image, markers);
			// on affiche le resultat de la detection sur une image
			for(unsigned int i=0; i<markers.size(); i++)
			{
				cout << markers[i];
				markers[i].draw(image, Scalar (0, 0, 255), 2);
			}
			imshow(windowName, image);
		}

		key = waitKey(1000.0 / 30.0); // 30 FPS
	}

	// Destroying the windows
	destroyWindow(windowName);
	// Releasing the video capture
	cap.release();

	return EXIT_SUCCESS;
}
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/gl.h>
#include <gl/glu.h>

void createCube(float points[8][3])
{
	glBegin(GL_QUADS);//draw some squares
	glColor3i(1, .9, .9);
	glVertex3fv(points[0]);
	glVertex3fv(points[1]);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);


	glColor3f(1, 1, .9);
	glVertex3fv(points[4]);
	glVertex3fv(points[5]);
	glVertex3fv(points[6]);
	glVertex3fv(points[7]);

	glColor3f(.1, 1, .9);
	glVertex3fv(points[1]);
	glVertex3fv(points[0]);
	glVertex3fv(points[4]);
	glVertex3fv(points[5]);

	glColor3f(.1, 1, .9);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);
	glVertex3fv(points[7]);
	glVertex3fv(points[6]);
	glEnd();
}

////////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////
int main()
{
	// Create the main window
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL");

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	//prepare OpenGL surface for HSR
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f, 0.3f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 700.0f);//fov, aspect, zNear, zFar



	bool rotate = false;
	auto speed = 0.0001;
	auto const velocity = 0.00001;
	float angle = 0;

	while (App.isOpen())
	{
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				App.close();

			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Escape)
					App.close();
				if (Event.key.code == sf::Keyboard::W)
					rotate = !rotate;
				if (Event.key.code == sf::Keyboard::A)
					speed -= velocity;
				if (Event.key.code == sf::Keyboard::D)
					speed += velocity;
			}

		}

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations for the cube
		glMatrixMode(GL_MODELVIEW);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);

		if (rotate) {
			angle += speed;
		}
		glRotatef(angle * 30, 1.f, 0.f, 0.f);
		glRotatef(angle * 20, 0.f, 1.f, 0.f);
		glRotatef(angle * 10, 0.f, 0.f, 1.f);

		const auto matrixXSize = 10;
		const auto matrixYSize = 12;
		const auto matrixZSize = 8;
		const auto tileXSize = 2;
		const auto tileYSize = 3;
		const auto tileZSize = 4;
		size_t tileXCount = matrixXSize / tileXSize;
		size_t tileYCount = matrixYSize / tileYSize;
		size_t tileZCount = matrixZSize / tileZSize;
		auto xSize = 200.f; auto xElemSize = xSize / tileXCount;
		auto ySize = 200.f; auto yElemSize = ySize / tileYCount;
		auto zSize = 100.f; auto zElemSize = zSize / tileZCount;
		auto xPos = -100.f;
		for (size_t i = 0; i < tileXCount; i++)
		{
			auto yPos = -100.f;
			for (size_t j = 0; j < tileYCount; j++)
			{
				auto zPos = -50.f;
				for (size_t k = 0; k < tileZCount; k++)
				{
					auto xEnd = xPos + xElemSize - 7.5;
					auto yEnd = yPos + yElemSize - 7.5;
					auto zEnd = zPos + zElemSize - 7.5;
					float pointsX[8][3] = {
						{ xPos, yPos, zPos },
						{ xPos, yEnd, zPos },
						{ xEnd, yEnd, zPos },
						{ xEnd, yPos, zPos },
						{ xPos, yPos, zEnd },
						{ xPos, yEnd, zEnd },
						{ xEnd, yEnd, zEnd },
						{ xEnd, yPos, zEnd }
					};
					createCube(pointsX);
					zPos += zElemSize;
				}
				yPos += yElemSize;
			}
			xPos += xElemSize;
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		xElemSize = xSize / 10;
		yElemSize = ySize / 10;
		zElemSize = zSize / 10;
		xPos = -100.f + 2.5;
		for (size_t i = 0; i < 10; i++)
		{
			auto yPos = -100.f + 2.5;
			for (size_t j = 0; j < 10; j++)
			{
				auto zPos = -50.f + 2.5;
				for (size_t k = 0; k < 10; k++)
				{
					auto xEnd = xPos + 1.5;
					auto yEnd = yPos + 1.5;
					auto zEnd = zPos + 1.5;
					float pointsX[8][3] = {
						{ xPos, yPos, zPos },
						{ xPos, yEnd, zPos },
						{ xEnd, yEnd, zPos },
						{ xEnd, yPos, zPos },
						{ xPos, yPos, zEnd },
						{ xPos, yEnd, zEnd },
						{ xEnd, yEnd, zEnd },
						{ xEnd, yPos, zEnd }
					};
					createCube(pointsX);
					zPos += zElemSize;
				}
				yPos += yElemSize;
			}
			xPos += xElemSize;
		}


		App.display();
	}

	return EXIT_SUCCESS;
}
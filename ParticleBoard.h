#pragma once
#include <SFML/Graphics.hpp>
#include "graph.h"
//#include "graph-backend-c.cpp"

class ParticleBoard
{
	unsigned int height;
	unsigned int width;
	float k;
	float g;

	bool isPaused;
	static bool spawnLockedCharge;
	static bool gravityOn;
	Graph graph;
public:
	struct Particle
	{
		float mass;
		float charge;

		sf::CircleShape shape;

		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Vector2f netForce;

		bool isLocked;

		//Construction
		Particle(float Mass, float Charge, sf::Vector2f pos);
		//Getters
		sf::CircleShape Shape();
		float Charge();
		float Mass();
		sf::Vector2f Position();
		sf::Vector2f Velocity();
		sf::Vector2f Acceleration();
		sf::Vector2f NetForce();

		//Kinematics
		void ApplyAccel();
		void ApplyVel();
		void ApplyForce();
		void CheckBoundaryCollision(unsigned int& height, unsigned int& width);

		//Movement

	};

	std::vector<Particle> particles;

	//======Construction/Destruction===========
	ParticleBoard(unsigned int Height, int Width, float coulombConst, float gravitationalConst);
	
	//======Getters/Setters====================
	unsigned int Height();
	unsigned int Width();
	float CoulombConst();
	float GravitationalConst();
	bool IsPaused();

	//=========Click and Key Functionality=============
	void LeftClick(sf::Vector2i mousePos, sf::RenderWindow& window);
	void RightClick(sf::Vector2i mousePos, sf::RenderWindow& window);
	void ResetVelocities();
	void TogglePause();
	static void ToggleLockedCharge();
	static void ToggleGravity();

	//=========Drawing=========================
	void Draw(sf::RenderWindow& window);

	//=========Movement and Forces=============
	void CalcNetForces();
	sf::Vector2f CalcCoulombsLaw(Particle& one, Particle& two);
	void UnitVector(sf::Vector2f& vec);//takes in a vector and makes it a unit vector in the same direction 
	float Hypotenuse(float x, float y);// returns c = sqrt(a^2, b^2) [pythagorean theorem]
	void MoveParticles();
};

#include "ParticleBoard.h"
#include <cmath>

/*===========================Construction/Destruction===================*/
bool ParticleBoard::spawnLockedCharge = false;
bool ParticleBoard::gravityOn = false;

ParticleBoard::ParticleBoard(unsigned int Height, int Width, float coulombConst, float gravitationalConst)
{
	height = Height;
	width = Width;
	k = coulombConst;
	g = gravitationalConst;
	isPaused = false;
	
}
ParticleBoard::Particle::Particle(float Mass, float Charge, sf::Vector2f pos)
{
	mass = Mass;
	charge = Charge;
	shape = sf::CircleShape(10.0f);

	position = pos;
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	netForce = sf::Vector2f(0, 0);

	if (spawnLockedCharge)
		isLocked = true;
	else
		isLocked = false;

	if (charge > 0)
	{
		if (isLocked)
			shape.setFillColor(sf::Color(255, 128, 0));
		else
			shape.setFillColor(sf::Color(255, 0, 0));
	}
	else
	{
		if (isLocked)
			shape.setFillColor(sf::Color(128, 0, 255));
		else
			shape.setFillColor(sf::Color(0, 0, 255));
	}
	shape.setPosition(position.x - shape.getRadius(), position.y - shape.getRadius());
}

/*===========================Getters/Setters=========================*/
//Board Data
unsigned int ParticleBoard::Height(){return height;}
unsigned int ParticleBoard::Width(){return width;}
float ParticleBoard::CoulombConst(){return k;}
float ParticleBoard::GravitationalConst(){return g;}
bool ParticleBoard::IsPaused() { return isPaused; }

//Particle Data
sf::CircleShape ParticleBoard::Particle::Shape() { return shape; }
float ParticleBoard::Particle::Charge() { return charge; }
float ParticleBoard::Particle::Mass() { return mass; }

sf::Vector2f ParticleBoard::Particle::Position() { return position; };
sf::Vector2f ParticleBoard::Particle::Velocity() { return velocity; };
sf::Vector2f ParticleBoard::Particle::Acceleration() { return acceleration; };
sf::Vector2f ParticleBoard::Particle::NetForce() { return netForce; };

/*=======================Click and Key Functionality=========================*/
void ParticleBoard::LeftClick(sf::Vector2i mousePos, sf::RenderWindow& window)
{
	particles.push_back(Particle(1, 1, sf::Vector2f(mousePos)));
}
void ParticleBoard::RightClick(sf::Vector2i mousePos, sf::RenderWindow& window)
{
	particles.push_back(Particle(1, -1, sf::Vector2f(mousePos)));
}
void ParticleBoard::ResetVelocities()
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles.at(i).velocity = sf::Vector2f(0, 0);
	}
}
void ParticleBoard::TogglePause() { isPaused = !isPaused; }
void ParticleBoard::ToggleLockedCharge() { spawnLockedCharge = !spawnLockedCharge; }
void ParticleBoard::ToggleGravity() { gravityOn = !gravityOn; }
/*=======================Drawing=====================================*/
void ParticleBoard::Draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		window.draw(particles.at(i).shape);
	}
}
/*======================Movement and Forces==========================*/
void ParticleBoard::CalcNetForces()
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles.at(i).netForce = sf::Vector2f(0, 0);
		//Apply Coulombs Law
		for (unsigned int j = 0; j < particles.size(); j++)
		{
			if (i != j)
			{
				
				particles.at(i).netForce += CalcCoulombsLaw(particles.at(i), particles.at(j));
			}
		}

		//Apply Simple Gravity
		if (gravityOn)
			particles.at(i).netForce += sf::Vector2f(0, g);


	}
}
sf::Vector2f ParticleBoard::CalcCoulombsLaw(Particle& one, Particle& two)
{
	float distance = hypot(one.position.x - two.position.x, one.position.y - two.position.y);

	sf::Vector2f force = (one.position - two.position);
	force /= hypot(force.x, force.y);
	force *= (k * one.Charge() * two.Charge());
	force /= distance;
	force /= distance;
	return force;
}
//void UnitVector(sf::Vector2f& vec)
//{
//	vec /= hypot(vec.x, vec.y);
//}

void ParticleBoard::MoveParticles()
{

	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles.at(i).ApplyForce();
		particles.at(i).ApplyAccel();
		particles.at(i).CheckBoundaryCollision(height, width);
		particles.at(i).ApplyVel();
	}
}
void ParticleBoard::Particle::ApplyVel()
{
	if (!isLocked)
	{
		shape.move(velocity);
		position += velocity;
	}
}
void ParticleBoard::Particle::ApplyAccel()
{
	velocity += acceleration;
}
void ParticleBoard::Particle::ApplyForce()
{
	acceleration = netForce / mass;
}
void ParticleBoard::Particle::CheckBoundaryCollision(unsigned int& height, unsigned int& width)
{
	sf::Vector2f peekPos = position + velocity;
	if (peekPos.x < 0 || peekPos.x > width)
		velocity.x *= -1;
	if (peekPos.y < 0 || peekPos.y > height)
		velocity.y *= -1;
}
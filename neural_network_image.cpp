#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>

typedef std::vector<float> vector_1d;
typedef std::vector<std::vector<float>> vector_2d;
typedef std::vector<std::vector<std::vector<float>>> vector_3d;

float sigmoid_derivative(float x) {
	return x * (1 - x);
}

float sigmoid(float x) {
	if (x > 5) {
		return 1;
	}
	else if (x < -5) {
		return 0;
	}
	else {
		return 1 / (1 + exp(-x));
	}
}

void init(int INPUT_NEURONS, int HIDDEN_NEURONS, int OUTPUT_NEURONS, int HIDDEN_LAYERS, vector_2d& neural_network, vector_3d& weights, vector_2d& biases, vector_2d& errors, vector_1d& expected_outputs, vector_1d& outputs, vector_1d& inputs) {
	std::mt19937 generator(rand() % 30);
	std::uniform_real_distribution<float> value_distribution(-1.0, 1.0);

	int LAYERS = HIDDEN_LAYERS + 2;

	//neural network resize
	neural_network.resize(LAYERS);
	neural_network[0].resize(INPUT_NEURONS);
	for (int i = 0; i < HIDDEN_LAYERS; i++) {
		neural_network[i + 1].resize(HIDDEN_NEURONS);
	}
	neural_network[LAYERS - 1].resize(OUTPUT_NEURONS);

	//weights resize
	weights.resize((LAYERS - 1));
	for (int i = 0; i < weights.size(); i++) {

		weights[i].resize(neural_network[i + 1].size());

		for (int j = 0; j < weights[i].size(); j++) {

			weights[i][j].resize(neural_network[i].size());

		}
	}
	for (int i = 0; i < weights.size(); i++) {

		for (int j = 0; j < weights[i].size(); j++) {

			for (int k = 0; k < weights[i][j].size(); k++) {

				weights[i][j][k] = value_distribution(generator);

			}
		}
	}

	//biases resize
	biases.resize(HIDDEN_LAYERS + 1);
	for (int i = 0; i < HIDDEN_LAYERS; i++) {
		biases[i].resize(HIDDEN_NEURONS);
	}
	biases[biases.size() - 1].resize(OUTPUT_NEURONS);

	for (int i = 0; i < biases.size(); i++) {
		for (int j = 0; j < biases[i].size(); j++) {
			biases[i][j] = 0;
		}
	}

	//errors resize
	errors.resize(HIDDEN_LAYERS + 1);
	for (int i = 0; i < HIDDEN_LAYERS; i++) {
		errors[i].resize(HIDDEN_NEURONS);
	}
	errors[errors.size() - 1].resize(OUTPUT_NEURONS);

	//other resize
	outputs.resize(OUTPUT_NEURONS);
	inputs.resize(INPUT_NEURONS);
	expected_outputs.resize(OUTPUT_NEURONS);
	//END INIT


}

vector_1d forward_propagation(const vector_1d& i_inputs, vector_2d& i_neural_network, const vector_3d& i_weights, const vector_2d& i_biases) {
	//inputs assignment
	for (int i = 0; i < i_inputs.size(); i++) {
		i_neural_network[0][i] = i_inputs[i];
	}

	//res neurons
	for (int i = 0; i < i_neural_network.size() - 1; i++) {
		for (int j = 0; j < i_neural_network[i + 1].size(); j++) {
			i_neural_network[i + 1][j] = 0;
		}
	}

	//forward propagation
	for (int i = 0; i < i_weights.size(); i++) {

		for (int j = 0; j < i_weights[i].size(); j++) {

			for (int k = 0; k < i_weights[i][j].size(); k++) {

				i_neural_network[1 + i][j] += i_neural_network[i][k] * i_weights[i][j][k];

			}

			i_neural_network[i + 1][j] += i_biases[i][j];


			i_neural_network[1 + i][j] = sigmoid(i_neural_network[1 + i][j]);

		}

	}



	//return outputs
	return i_neural_network[i_neural_network.size() - 1];

}

void back_propagation(const vector_1d& expected_outputs, vector_3d& i_weights, vector_2d& errors, const vector_2d& i_neural_network, vector_2d& biases, const float LEARNING_RATE) {
	//res errors
	for (int i = 0; i < errors.size(); i++) {
		for (int j = 0; j < errors[i].size(); j++) {
			errors[i][j] = 0;
		}
	}


	//1st layer of weights (closest to output)
	for (int i = 0; i < i_weights[i_weights.size() - 1].size(); i++) {
		for (int j = 0; j < i_weights[i_weights.size() - 1][i].size(); j++) {
			i_weights[i_weights.size() - 1][i][j] -= LEARNING_RATE * 2 * (i_neural_network[i_neural_network.size() - 1][i] - expected_outputs[i]) * sigmoid_derivative(i_neural_network[i_neural_network.size() - 1][i]) * i_neural_network[i_neural_network.size() - 2][j];
		}
	}

	//main errors
	for (int i = 0; i < errors[errors.size() - 1].size(); i++) {
		errors[errors.size() - 1][i] = pow(i_neural_network[i_neural_network.size() - 1][i] - expected_outputs[i], 1);
	}

	//errors in other layers
	for (int i = 0; i < i_weights.size() - 1; i++) {

		for (int j = 0; j < i_weights[i_weights.size() - 1 - i].size(); j++) {

			for (int k = 0; k < errors[errors.size() - 2 - i].size(); k++) {

				errors[errors.size() - 2 - i][k] += errors[errors.size() - 1 - i][j] * i_weights[i_weights.size() - 1 - i][j][k] * sigmoid_derivative(i_neural_network[i_neural_network.size() - 1 - i][j]);

			}

		}

	}


	//other layers weights alteration
	for (int i = 0; i < i_weights.size() - 1; i++) {

		for (int j = 0; j < i_weights[i_weights.size() - 2 - i].size(); j++) {

			for (int k = 0; k < i_weights[i_weights.size() - 2 - i][j].size(); k++) {


				i_weights[i_weights.size() - 2 - i][j][k] -= LEARNING_RATE * 2 * errors[i_weights.size() - 2 - i][j] * sigmoid_derivative(i_neural_network[i_weights.size() - 1 - i][j]) * i_neural_network[i_weights.size() - 2 - i][k];


			}
		}
	}

	//biases alteration
	for (int i = 0; i < biases.size(); i++) {
		for (int j = 0; j < biases[i].size(); j++) {

			biases[i][j] -= LEARNING_RATE * 2 * errors[i][j];

		}
	}



}


int main() {
	srand(time(NULL));

	//INIT
	int INPUT_NEURONS = 2;
	int HIDDEN_NEURONS = 100;
	int OUTPUT_NEURONS = 3;
	int HIDDEN_LAYERS = 3;
	int LAYERS = HIDDEN_LAYERS + 2;
	float LEARNING_RATE = 0.005;

	vector_2d neural_network;
	vector_3d weights;
	vector_2d biases;
	vector_2d errors;
	vector_1d expected_outputs;
	vector_1d outputs;
	vector_1d inputs;

	init(INPUT_NEURONS, HIDDEN_NEURONS, OUTPUT_NEURONS, HIDDEN_LAYERS, neural_network, weights, biases, errors, expected_outputs, outputs, inputs);

	sf::RenderWindow okno(sf::VideoMode(1024, 768), "AI");

	sf::RectangleShape tlo(sf::Vector2f(1024, 768));
	tlo.setFillColor(sf::Color::White);

	sf::Image outputs_image;
	outputs_image.create(50, 50);
	sf::Sprite outputs_sprite;
	sf::Texture outputs_texture;
	outputs_texture.loadFromImage(outputs_image);

	outputs_texture.update(outputs_image);
	outputs_sprite.setTexture(outputs_texture);
	outputs_sprite.setScale(sf::Vector2f(15, 15));
	outputs_sprite.setPosition(sf::Vector2f(120, 10));

	expected_outputs[0] = 1;
	sf::Clock zegarek;

	vector_2d punkty_in;
	vector_2d out;

	std::vector<sf::CircleShape> kolka;

	int rgb = 1;


	while (okno.isOpen()) {
		okno.clear();
		okno.draw(tlo);

		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				okno.close();

			}
		}

		if (rgb == 0) {

			if (event.type == sf::Event::MouseButtonPressed) {
				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
				{
					int mouse_x = (sf::Mouse::getPosition(okno).x - 120) / 15;
					int mouse_y = (sf::Mouse::getPosition(okno).y - 10) / 15;
					punkty_in.push_back({ float(mouse_x) / 10,float(mouse_y) / 10 });
					out.push_back({ 0 });
					sf::CircleShape kolo0(10);
					kolo0.setPosition(sf::Vector2f(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y));
					kolo0.setFillColor(sf::Color::White);
					kolo0.setOutlineColor(sf::Color::Red);
					kolo0.setOutlineThickness(1);

					kolka.push_back(kolo0);
					break;
				}
				case sf::Mouse::Right:
				{
					int mouse_x = (sf::Mouse::getPosition(okno).x - 120) / 15;
					int mouse_y = (sf::Mouse::getPosition(okno).y - 10) / 15;
					punkty_in.push_back({ float(mouse_x) / 10,float(mouse_y) / 10 });
					out.push_back({ 1 });
					sf::CircleShape kolo0(10);
					kolo0.setPosition(sf::Vector2f(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y));
					kolo0.setFillColor(sf::Color::Black);
					kolo0.setOutlineColor(sf::Color::Red);
					kolo0.setOutlineThickness(1);

					kolka.push_back(kolo0);

					break;
				}
				}


			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
				for (int i = 0; i < 45; i++) {
					int x = rand() % 50;
					int y = rand() % 50;
					inputs[0] = float(x) / 10;
					inputs[1] = float(y) / 10;
					outputs = forward_propagation(inputs, neural_network, weights, biases);
					outputs_image.setPixel(x, y, sf::Color(round(255 * outputs[0])));
					outputs_texture.update(outputs_image);
				}
				if (zegarek.getElapsedTime().asMilliseconds() > 0.01) {
					int x = rand() % punkty_in.size();
					outputs = forward_propagation(punkty_in[x], neural_network, weights, biases);
					back_propagation(out[x], weights, errors, neural_network, biases, LEARNING_RATE);
					zegarek.restart();
				}


			}

			okno.draw(outputs_sprite);
			for (int i = 0; i < kolka.size(); i++) {
				okno.draw(kolka[i]);
			}
		}
		
		if (rgb == 1) {

			if (event.type == sf::Event::MouseButtonPressed) {
				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
				{
					int mouse_x = (sf::Mouse::getPosition(okno).x - 120) / 15;
					int mouse_y = (sf::Mouse::getPosition(okno).y - 10) / 15;
					punkty_in.push_back({ float(mouse_x) / 10,float(mouse_y) / 10 });
					out.push_back({ 1,0,0 });
					sf::CircleShape kolo0(10);
					kolo0.setPosition(sf::Vector2f(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y));
					kolo0.setFillColor(sf::Color::Red);
					kolo0.setOutlineColor(sf::Color::Red);
					kolo0.setOutlineThickness(1);

					kolka.push_back(kolo0);
					break;
				}
				case sf::Mouse::Right:
				{
					int mouse_x = (sf::Mouse::getPosition(okno).x - 120) / 15;
					int mouse_y = (sf::Mouse::getPosition(okno).y - 10) / 15;
					punkty_in.push_back({ float(mouse_x) / 10,float(mouse_y) / 10 });
					out.push_back({ 0,1,0 });
					sf::CircleShape kolo0(10);
					kolo0.setPosition(sf::Vector2f(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y));
					kolo0.setFillColor(sf::Color::Green);
					kolo0.setOutlineColor(sf::Color::Red);
					kolo0.setOutlineThickness(1);

					kolka.push_back(kolo0);

					break;
				}
				case sf::Mouse::Middle:
				{
					int mouse_x = (sf::Mouse::getPosition(okno).x - 120) / 15;
					int mouse_y = (sf::Mouse::getPosition(okno).y - 10) / 15;
					punkty_in.push_back({ float(mouse_x) / 10,float(mouse_y) / 10 });
					out.push_back({ 0,0,1 });
					sf::CircleShape kolo0(10);
					kolo0.setPosition(sf::Vector2f(sf::Mouse::getPosition(okno).x, sf::Mouse::getPosition(okno).y));
					kolo0.setFillColor(sf::Color::Blue);
					kolo0.setOutlineColor(sf::Color::Red);
					kolo0.setOutlineThickness(1);

					kolka.push_back(kolo0);

					break;
				}
				}


			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
				for (int i = 0; i < 35; i++) {
					int x = rand() % 50;
					int y = rand() % 50;
					inputs[0] = float(x) / 10;
					inputs[1] = float(y) / 10;
					outputs = forward_propagation(inputs, neural_network, weights, biases);
					outputs_image.setPixel(x, y, sf::Color(round(255 * outputs[0]), round(255 * outputs[1]), round(255 * outputs[2])));
					outputs_texture.update(outputs_image);
				}
				
				if (zegarek.getElapsedTime().asMilliseconds() > 0.01) {
					int x = rand() % punkty_in.size();
					outputs = forward_propagation(punkty_in[x], neural_network, weights, biases);
					back_propagation(out[x], weights, errors, neural_network, biases, LEARNING_RATE);
					zegarek.restart();
				}


			}

			okno.draw(outputs_sprite);
			for (int i = 0; i < kolka.size(); i++) {
				okno.draw(kolka[i]);
			}

		}


		okno.display();

		

	}

}
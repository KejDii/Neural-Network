//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <iomanip>
//#include <random>
//#include <ctime>
//#include <cstdlib>
//#include <vector>
//#include <array>
//
//typedef std::vector<float> vector_1d;
//typedef std::vector<std::vector<float>> vector_2d;
//typedef std::vector<std::vector<std::vector<float>>> vector_3d;
//
//float sigmoid_derivative(float x) {
//	return x * (1 - x);
//}
//
//float sigmoid(float x) {
//	if (x > 5) {
//		return 1;
//	}
//	else if (x < -5) {
//		return 0;
//	}
//	else {
//		return 1 / (1 + exp(-x));
//	}
//	}
//
//void init(int INPUT_NEURONS, int HIDDEN_NEURONS, int OUTPUT_NEURONS, int HIDDEN_LAYERS, vector_2d &neural_network, vector_3d &weights, vector_2d &biases, vector_2d &errors, vector_1d& expected_outputs, vector_1d &outputs, vector_1d &inputs) {
//	std::mt19937 generator(rand() % 30);
//	std::uniform_real_distribution<float> value_distribution(-1.0, 1.0);
//	
//	int LAYERS = HIDDEN_LAYERS + 2;
//
//	//neural network resize
//	neural_network.resize(LAYERS);
//	neural_network[0].resize(INPUT_NEURONS);
//	for (int i = 0; i < HIDDEN_LAYERS; i++) {
//		neural_network[i + 1].resize(HIDDEN_NEURONS);
//	}
//	neural_network[LAYERS - 1].resize(OUTPUT_NEURONS);
//
//	//weights resize
//	weights.resize((LAYERS - 1));
//	for (int i = 0; i < weights.size(); i++) {
//
//		weights[i].resize(neural_network[i + 1].size());
//
//		for (int j = 0; j < weights[i].size(); j++) {
//
//			weights[i][j].resize(neural_network[i].size());
//
//		}
//	}
//	for (int i = 0; i < weights.size(); i++) {
//
//		for (int j = 0; j < weights[i].size(); j++) {
//
//			for (int k = 0; k < weights[i][j].size(); k++) {
//
//				weights[i][j][k] = value_distribution(generator);
//
//			}
//		}
//	}
//
//	//biases resize
//	biases.resize(HIDDEN_LAYERS + 1);
//	for (int i = 0; i < HIDDEN_LAYERS; i++) {
//		biases[i].resize(HIDDEN_NEURONS);
//	}
//	biases[biases.size() - 1].resize(OUTPUT_NEURONS);
//
//	for (int i = 0; i < biases.size(); i++) {
//		for (int j = 0; j < biases[i].size(); j++) {
//			biases[i][j] = 0;
//		}
//	}
//
//	//errors resize
//	errors.resize(HIDDEN_LAYERS + 1);
//	for (int i = 0; i < HIDDEN_LAYERS; i++) {
//		errors[i].resize(HIDDEN_NEURONS);
//	}
//	errors[errors.size() - 1].resize(OUTPUT_NEURONS);
//
//	//other resize
//	outputs.resize(OUTPUT_NEURONS);
//	inputs.resize(INPUT_NEURONS);
//	expected_outputs.resize(OUTPUT_NEURONS);
//	//END INIT
//
//
//}
//
//vector_1d forward_propagation(const vector_1d& i_inputs, vector_2d& i_neural_network, const vector_3d& i_weights, const vector_2d& i_biases) {
//	//inputs assignment
//	for (int i = 0; i < i_inputs.size(); i++) {
//		i_neural_network[0][i] = i_inputs[i];
//	}
//	
//	//res neurons
//	for (int i = 0; i < i_neural_network.size()-1; i++) {
//		for (int j = 0; j < i_neural_network[i + 1].size(); j++) {
//			i_neural_network[i+1][j] = 0;
//		}
//	}
//
//	//forward propagation
//	for (int i = 0; i < i_weights.size(); i++) {
//
//		for (int j = 0; j < i_weights[i].size(); j++) {
//
//			for (int k = 0; k < i_weights[i][j].size(); k++) {
//
//				i_neural_network[1 + i][j] += i_neural_network[i][k] * i_weights[i][j][k];
//				
//			}
//			
//			i_neural_network[i + 1][j] += i_biases[i][j];
//
//
//			i_neural_network[1 + i][j] = sigmoid(i_neural_network[1 + i][j]);
//			
//		}
//
//	}
//
//
//
//	//return outputs
//	return i_neural_network[i_neural_network.size() - 1];
//
//}
//
//void back_propagation(const vector_1d& expected_outputs, vector_3d& i_weights, vector_2d& errors, const vector_2d& i_neural_network, vector_2d& biases, const float LEARNING_RATE) {
//	//res errors
//	for (int i = 0; i < errors.size(); i++) {
//		for (int j = 0; j < errors[i].size(); j++) {
//			errors[i][j] = 0;
//		}
//	}
//
//
//	//1st layer of weights (closest to output)
//	for (int i = 0; i < i_weights[i_weights.size() - 1].size(); i++) {
//		for (int j = 0; j < i_weights[i_weights.size() - 1][i].size(); j++) {
//			i_weights[i_weights.size() - 1][i][j] -= LEARNING_RATE * 2 * (i_neural_network[i_neural_network.size() - 1][i] - expected_outputs[i]) * sigmoid_derivative(i_neural_network[i_neural_network.size() - 1][i]) * i_neural_network[i_neural_network.size() - 2][j];
//		}
//	}
//
//	//main errors
//	for (int i = 0; i < errors[errors.size() - 1].size(); i++) {
//		errors[errors.size() - 1][i] = pow(i_neural_network[i_neural_network.size() - 1][i] - expected_outputs[i], 1);
//	}
//
//	//errors in other layers
//	for (int i = 0; i < i_weights.size() - 1; i++) {
//		
//		for (int j = 0; j < i_weights[i_weights.size()-1-i].size(); j++) {
//			
//			for (int k = 0; k < errors[errors.size()-2-i].size(); k++) {
//				
//				errors[errors.size() - 2 - i][k] += errors[errors.size() - 1 - i][j] * i_weights[i_weights.size() - 1 - i][j][k]*sigmoid_derivative(i_neural_network[i_neural_network.size()-1-i][j]);
//			
//			}
//			
//		}
//
//	}
//
//	
//	//other layers weights alteration
//	for (int i = 0; i < i_weights.size() - 1; i++) {
//		
//		for (int j = 0; j < i_weights[i_weights.size() - 2 - i].size(); j++) {
//			
//			for (int k = 0; k < i_weights[i_weights.size() - 2 - i][j].size(); k++) {
//				
//
//				i_weights[i_weights.size() - 2 - i][j][k] -= LEARNING_RATE * 2 * errors[i_weights.size() - 2 - i][j]*sigmoid_derivative(i_neural_network[i_weights.size() - 1 - i][j])* i_neural_network[i_weights.size() - 2 - i][k];
//				
//
//			}
//		}
//	}
//	
//	//biases alteration
//	for (int i = 0; i < biases.size(); i++) {
//		for (int j = 0; j < biases[i].size(); j++) {
//
//			biases[i][j] -= LEARNING_RATE * 2 * errors[i][j];
//
//		}
//	}
//	
//
//
//}
//
//void xored(vector_1d&inputs,vector_1d& expected_outputs) {
//	int x = rand() % 4;
//	if (x == 0) {
//		inputs[0] = 0;
//		inputs[1] = 0;
//		expected_outputs[0] = 0;
//	}
//	else if (x == 1) {
//		inputs[0] = 0;
//		inputs[1] = 1;
//		expected_outputs[0] = 1;
//	}
//	else if (x == 2) {
//		inputs[0] = 1;
//		inputs[1] = 0;
//		expected_outputs[0] = 1;
//	}
//	else if (x == 3) {
//		inputs[0] = 1;
//		inputs[1] = 1;
//		expected_outputs[0] = 0;
//	}
//}
//
//void funkcja2(vector_1d& inputs, vector_1d& expected_outputs) {
//	int x = rand() % 8;
//	if (x == 0) {
//		inputs[0] = 0;
//		inputs[1] = 0;
//		inputs[2] = 0;
//		expected_outputs[0] = 1;
//		expected_outputs[1] = 0;
//	}
//	else if (x == 1) {
//		inputs[0] = 0;
//		inputs[1] = 0;
//		inputs[2] = 1;
//		expected_outputs[0] = 1;
//		expected_outputs[1] = 0;
//	}
//	else if (x == 2) {
//		inputs[0] = 0;
//		inputs[1] = 1;
//		inputs[2] = 0;
//		expected_outputs[0] = 1;
//		expected_outputs[1] = 0;
//	}
//	else if (x == 3) {
//		inputs[0] = 0;
//		inputs[1] = 1;
//		inputs[2] = 1;
//		expected_outputs[0] = 0;
//		expected_outputs[1] = 1;
//	}
//	else if (x == 4) {
//		inputs[0] = 1;
//		inputs[1] = 0;
//		inputs[2] = 0;
//		expected_outputs[0] = 1;
//		expected_outputs[1] = 0;
//	}
//	else if (x == 5) {
//		inputs[0] = 1;
//		inputs[1] = 0;
//		inputs[2] = 1;
//		expected_outputs[0] = 0;
//		expected_outputs[1] = 1;
//	}
//	else if (x == 6) {
//		inputs[0] = 1;
//		inputs[1] = 1;
//		inputs[2] = 0;
//		expected_outputs[0] = 0;
//		expected_outputs[1] = 0;
//	}
//	else if (x == 7) {
//		inputs[0] = 1;
//		inputs[1] = 1;
//		inputs[2] = 1;
//		expected_outputs[0] = 0;
//		expected_outputs[1] = 1;
//	}
//}
//
//
//int main() {
//	srand(time(NULL));
//	
//	//INIT
//	int INPUT_NEURONS = 3;
//	int HIDDEN_NEURONS = 20;
//	int OUTPUT_NEURONS = 2;
//	int HIDDEN_LAYERS = 2;
//	int LAYERS = HIDDEN_LAYERS + 2;
//	float LEARNING_RATE = 0.01;
//
//	vector_2d neural_network;
//	vector_3d weights;
//	vector_2d biases;
//	vector_2d errors;
//	vector_1d expected_outputs;
//	vector_1d outputs;
//	vector_1d inputs;
//
//	init(INPUT_NEURONS, HIDDEN_NEURONS, OUTPUT_NEURONS, HIDDEN_LAYERS, neural_network, weights, biases, errors, expected_outputs, outputs, inputs);
//
//	
//	
//	//testing (sfml)
//	sf::RenderWindow okno(sf::VideoMode(1024, 768), "AI");
//	sf::Text napisy[5];
//	sf::Font* czcionka = new sf::Font;
//	czcionka->loadFromFile("Arialn.ttf");
//	napisy[0].setFont(*czcionka);
//	napisy[1].setFont(*czcionka);
//	napisy[2].setFont(*czcionka);
//	napisy[3].setFont(*czcionka);
//	napisy[4].setFont(*czcionka);
//	napisy[0].setCharacterSize(30);
//	napisy[1].setCharacterSize(30);
//	napisy[2].setCharacterSize(30);
//	napisy[3].setCharacterSize(30);
//	napisy[4].setCharacterSize(30);
//	napisy[0].setPosition(sf::Vector2f(200, 300));
//	napisy[1].setPosition(sf::Vector2f(200, 400));
//	napisy[2].setPosition(sf::Vector2f(200, 500));
//	napisy[3].setPosition(sf::Vector2f(600, 300));
//	napisy[4].setPosition(sf::Vector2f(600, 400));
//
//	while (okno.isOpen()) {
//
//		sf::Event event;
//		while (okno.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				okno.close();
//
//			}
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
//			//nauka
//			funkcja2(inputs, expected_outputs);
//
//			outputs = forward_propagation(inputs, neural_network, weights, biases);
//
//			napisy[0].setString(std::to_string(inputs[0]));
//			napisy[1].setString(std::to_string(inputs[1]));
//			napisy[2].setString(std::to_string(inputs[2]));
//			napisy[3].setString(std::to_string(outputs[0]));
//			napisy[4].setString(std::to_string(outputs[1]));
//			
//
//			back_propagation(expected_outputs, weights, errors, neural_network, biases, LEARNING_RATE);
//			
//			
//		}
//		
//		okno.display();
//		
//		okno.clear();
//		for (int i = 0; i < 5; i++) {
//			okno.draw(napisy[i]);
//		}
//
//	}
//}
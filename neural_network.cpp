//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <chrono>
//#include <iomanip>
//#include <random>
//#include <ctime>
//#include <cstdlib>
//#include <vector>
//#include <array>
//
//float sigmoid_derivative(float x) {
//	return x * (1 - x);
//}
//
//float sigmoid(float x) {
//	return 1 / (1 + exp(-x));
//}
//
//class Neuron {
//private:
//	sf::CircleShape kolo;
//	sf::Text liczba;
//	float wartosc;
//	float bias;
//public:
//	Neuron();
//	void draw(sf::RenderWindow&okno);
//	void setPos(int x, int y);
//	void setCol(sf::Color kolor);
//	void conf(int layers, int ilosc_neuronow, int szerokosc_okna, int wysokosc_okna, sf::Color kolor,int iter_neuron,int iter_layer);
//	void setWartosc(float random);
//	float getWartosc();
//	float getBias();
//	void setBias(float rate,float blad);
//};
//
//Neuron::Neuron() {
//	wartosc = 3;
//	bias = 0;
//	kolo.setRadius(30);
//	kolo.setOutlineThickness(2);
//	kolo.setOutlineColor(sf::Color::White);
//	
//	
//}
//
//void Neuron::setBias(float rate,float blad) {
//	bias += rate * blad;
//}
//
//void losowo(Neuron* input, float& oczekiwany) {
//	int x = rand() % 4;
//	if (x == 0) {
//		input[0].setWartosc(0);
//		input[1].setWartosc(1);
//		oczekiwany = 1;
//	}
//	else if (x == 1) {
//		input[0].setWartosc(1);
//		input[1].setWartosc(0);
//		oczekiwany = 1;
//	}
//	else if (x == 2) {
//		input[0].setWartosc(0);
//		input[1].setWartosc(0);
//		oczekiwany = 0;
//	}
//	else
//	{
//		input[0].setWartosc(1);
//		input[1].setWartosc(1);
//		oczekiwany = 0;
//	}
//
//}
//
//float Neuron::getWartosc() {
//	return wartosc;
//}
//float Neuron::getBias() {
//	return bias;
//}
//
//void Neuron::setWartosc(float random) {
//	wartosc = random;
//}
//
//void Neuron::draw(sf::RenderWindow&okno) {
//	okno.draw(kolo);
//	liczba.setString(std::to_string(wartosc));
//	okno.draw(liczba);
//}
//
//void Neuron::setPos(int x, int y) {
//	kolo.setPosition(sf::Vector2f(x, y));
//}
//
//void Neuron::setCol(sf::Color kolor) {
//	kolo.setFillColor(kolor);
//}
//
//void Neuron::conf(int layers, int ilosc_neuronow, int szerokosc_okna, int wysokosc_okna, sf::Color kolor,int iter_neuron,int iter_layer) {
//	kolo.setFillColor(kolor);
//	kolo.setPosition(sf::Vector2f((iter_layer)*szerokosc_okna / (layers+1), (iter_neuron+1)*wysokosc_okna / (ilosc_neuronow+1)));
//	
//	liczba.setPosition(sf::Vector2f(kolo.getPosition().x + 15, kolo.getPosition().y + 15));
//	liczba.setCharacterSize(20);
//	liczba.setString(std::to_string(wartosc));
//	sf::Font* czcionka = new sf::Font;
//	czcionka->loadFromFile("Arialn.ttf");
//	liczba.setFont(*czcionka);
//}
//
//int main() {
//	float LEARNING_RATE = 0.01;
//	int szerokosc_okna = 1024;
//	int wysokosc_okna = 768;
//	int inp = 2;
//	sf::Font* czcion = new sf::Font;
//	czcion->loadFromFile("Arialn.ttf");
//	sf::Text nauka;
//	nauka.setString("NAUKA");
//	nauka.setCharacterSize(40);
//	nauka.setOutlineThickness(3);
//	nauka.setFillColor(sf::Color::Red);
//	nauka.setOutlineColor(sf::Color::White);
//	nauka.setPosition(sf::Vector2f(480, 650));
//	nauka.setFont(*czcion);
//
//	sf::Text co;
//	co.setCharacterSize(40);
//	co.setFillColor(sf::Color::Red);
//	co.setPosition(sf::Vector2f(480, 650));
//	co.setFont(*czcion);
//	co.setOutlineColor(sf::Color::White);
//	co.setOutlineThickness(3);
//
//	sf::Text xored;
//	xored.setCharacterSize(30);
//	xored.setFillColor(sf::Color::Green);
//	xored.setPosition(sf::Vector2f(160, 768/2));
//	xored.setFont(*czcion);
//	xored.setOutlineColor(sf::Color::White);
//	xored.setOutlineThickness(1);
//	xored.setString("XOR");
//
//	sf::Text outlayer;
//	sf::Text inlayer;
//	sf::Text hidlayer;
//
//	outlayer.setString("Output Layer");
//	outlayer.setCharacterSize(35);
//	outlayer.setFillColor(sf::Color::Yellow);
//	outlayer.setPosition(sf::Vector2f((3*1024/4)-30, 40));
//	outlayer.setFont(*czcion);
//	outlayer.setOutlineColor(sf::Color::White);
//	outlayer.setOutlineThickness(1);
//
//	inlayer.setString("Input Layer");
//	inlayer.setCharacterSize(35);
//	inlayer.setFillColor(sf::Color::Yellow);
//	inlayer.setPosition(sf::Vector2f((1 * 1024 / 4) - 30, 40));
//	inlayer.setFont(*czcion);
//	inlayer.setOutlineColor(sf::Color::White);
//	inlayer.setOutlineThickness(1);
//
//	hidlayer.setString("Hidden Layer");
//	hidlayer.setCharacterSize(35);
//	hidlayer.setFillColor(sf::Color::Yellow);
//	hidlayer.setPosition(sf::Vector2f((2 * 1024 / 4) - 30, 40));
//	hidlayer.setFont(*czcion);
//	hidlayer.setOutlineColor(sf::Color::White);
//	hidlayer.setOutlineThickness(1);
//
//
//	srand(time(NULL));
//	std::random_device rd{};
//	std::mt19937 generator(rd());
//	std::uniform_real_distribution<float> neuron_dystrybucja(-1, 1);
//
//
//	sf::RenderWindow okno(sf::VideoMode(szerokosc_okna, wysokosc_okna), "AI");
//	Neuron inputLayer[2];
//	for (int i = 0; i < 2; i++) {
//		inputLayer[i].setWartosc(neuron_dystrybucja(generator));
//		inputLayer[i].conf(3, 2, szerokosc_okna, wysokosc_okna, sf::Color::Red, i, 1);
//		
//	}
//	
//	
//	Neuron hiddenLayer[3];
//	for (int i = 0; i < 3; i++) {
//		hiddenLayer[i].setWartosc(neuron_dystrybucja(generator));
//		hiddenLayer[i].conf(3, 3, szerokosc_okna, wysokosc_okna, sf::Color::Green, i, 2);
//		
//	}
//	
//	Neuron outputLayer;
//	outputLayer.conf(3, 1, szerokosc_okna, wysokosc_okna, sf::Color::Blue, 0, 3);
//
//	float wagi_I_H[2][3] = { 0 };
//	float wagi_H_O[3] = { 0 };
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < 3; j++) {
//			wagi_I_H[i][j] = neuron_dystrybucja(generator);
//			wagi_H_O[j] = neuron_dystrybucja(generator);
//		}
//	}
//
//
//	inputLayer[0].setWartosc(1);
//	inputLayer[1].setWartosc(0);
//
//	float x = inputLayer[0].getWartosc() * wagi_I_H[0][0] + inputLayer[1].getWartosc() * wagi_I_H[1][0] + hiddenLayer[0].getBias();
//	hiddenLayer[0].setWartosc(1 / (1 + exp(-x)));
//	x = inputLayer[0].getWartosc() * wagi_I_H[0][1] + inputLayer[1].getWartosc() * wagi_I_H[1][1] + hiddenLayer[1].getBias();
//	hiddenLayer[1].setWartosc(1 / (1 + exp(-x)));
//	x = inputLayer[0].getWartosc() * wagi_I_H[0][2] + inputLayer[1].getWartosc() * wagi_I_H[1][2] + hiddenLayer[2].getBias();
//	hiddenLayer[2].setWartosc(1 / (1 + exp(-x)));
//
//	x = hiddenLayer[0].getWartosc() * wagi_H_O[0] + hiddenLayer[1].getWartosc() * wagi_H_O[1] + hiddenLayer[2].getWartosc() * wagi_H_O[2];
//	outputLayer.setWartosc(1 / (1 + exp(-x)));
//
//	float oczekiwany = 1;
//	float blad_glowny = pow(oczekiwany - outputLayer.getWartosc(), 2);
//	float blad_poch = 2 * (outputLayer.getWartosc() - oczekiwany);
//	wagi_H_O[0] -= LEARNING_RATE * 2 * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * hiddenLayer[0].getWartosc();
//	wagi_H_O[1] -= LEARNING_RATE * 2 * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * hiddenLayer[1].getWartosc();
//	wagi_H_O[2] -= LEARNING_RATE * 2 * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * hiddenLayer[2].getWartosc();
//	//outputLayer.setBias(LEARNING_RATE, blad_glowny);
//
//	float bledy[3] = { 0 };
//	bledy[0] = sigmoid(blad_glowny * wagi_H_O[0] + hiddenLayer[0].getBias());
//	bledy[1] = sigmoid(blad_glowny * wagi_H_O[1] + hiddenLayer[1].getBias());
//	bledy[2] = sigmoid(blad_glowny * wagi_H_O[2] + hiddenLayer[2].getBias());
//
//	//hiddenLayer[0].setBias(LEARNING_RATE, bledy[0]);
//	//hiddenLayer[1].setBias(LEARNING_RATE, bledy[1]);
//	//hiddenLayer[2].setBias(LEARNING_RATE, bledy[2]);
//
//	wagi_I_H[0][0] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[0] * sigmoid_derivative(hiddenLayer[0].getWartosc()) * inputLayer[0].getWartosc();
//	wagi_I_H[0][1] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[1] * sigmoid_derivative(hiddenLayer[1].getWartosc()) * inputLayer[0].getWartosc();
//	wagi_I_H[0][2] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[2] * sigmoid_derivative(hiddenLayer[2].getWartosc()) * inputLayer[0].getWartosc();
//
//	wagi_I_H[1][0] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[0] * sigmoid_derivative(hiddenLayer[0].getWartosc()) * inputLayer[1].getWartosc();
//	wagi_I_H[1][1] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[1] * sigmoid_derivative(hiddenLayer[1].getWartosc()) * inputLayer[1].getWartosc();
//	wagi_I_H[1][2] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[2] * sigmoid_derivative(hiddenLayer[2].getWartosc()) * inputLayer[1].getWartosc();
//
//	sf::Image outputs_image;
//	outputs_image.create(100, 100);
//	outputs_image.setPixel(10, 10, sf::Color::White);
//	
//	sf::Texture outputs_texture;
//	outputs_texture.loadFromImage(outputs_image);
//	
//	sf::Sprite outputs_sprite;
//	outputs_sprite.setPosition(sf::Vector2f(10, 10));
//	outputs_sprite.setTexture(outputs_texture);
//	outputs_sprite.setScale(sf::Vector2f(10,10));
//	
//	
//
//
//	sf::Clock zegarek;
//	while (okno.isOpen()) {
//
//		sf::Event event;
//		while (okno.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				okno.close();
//			}
//		}
//
//		if (zegarek.getElapsedTime().asMicroseconds() > 0.01) {
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
//				//nauka
//				inputLayer[0].setWartosc(1);
//				inputLayer[1].setWartosc(0);
//				float oczekiwany = 1;
//				losowo(inputLayer, oczekiwany);
//
//				float x = inputLayer[0].getWartosc() * wagi_I_H[0][0] + inputLayer[1].getWartosc() * wagi_I_H[1][0] + hiddenLayer[0].getBias();
//				hiddenLayer[0].setWartosc(1 / (1 + exp(-x)));
//				x = inputLayer[0].getWartosc() * wagi_I_H[0][1] + inputLayer[1].getWartosc() * wagi_I_H[1][1] + hiddenLayer[1].getBias();
//				hiddenLayer[1].setWartosc(1 / (1 + exp(-x)));
//				x = inputLayer[0].getWartosc() * wagi_I_H[0][2] + inputLayer[1].getWartosc() * wagi_I_H[1][2] + hiddenLayer[2].getBias();
//				hiddenLayer[2].setWartosc(1 / (1 + exp(-x)));
//
//				x = hiddenLayer[0].getWartosc() * wagi_H_O[0] + hiddenLayer[1].getWartosc() * wagi_H_O[1] + hiddenLayer[2].getWartosc() * wagi_H_O[2];
//				outputLayer.setWartosc(1 / (1 + exp(-x)));
//
//				
//				float blad_glowny = pow(oczekiwany - outputLayer.getWartosc(), 2);
//				float blad_poch = 2 * (outputLayer.getWartosc() - oczekiwany);
//				wagi_H_O[0] -= LEARNING_RATE * 2*blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * hiddenLayer[0].getWartosc();
//				wagi_H_O[1] -= LEARNING_RATE * 2 * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * hiddenLayer[1].getWartosc();
//				wagi_H_O[2] -= LEARNING_RATE * 2 * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * hiddenLayer[2].getWartosc();
//				//outputLayer.setBias(LEARNING_RATE, blad_glowny);
//
//				float bledy[3] = { 0 };
//				bledy[0] = sigmoid(blad_glowny * wagi_H_O[0] + hiddenLayer[0].getBias());
//				bledy[1] = sigmoid(blad_glowny * wagi_H_O[1] + hiddenLayer[1].getBias());
//				bledy[2] = sigmoid(blad_glowny * wagi_H_O[2] + hiddenLayer[2].getBias());
//
//				//hiddenLayer[0].setBias(LEARNING_RATE, bledy[0]);
//				//hiddenLayer[1].setBias(LEARNING_RATE, bledy[1]);
//				//hiddenLayer[2].setBias(LEARNING_RATE, bledy[2]);
//
//				wagi_I_H[0][0] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[0]*sigmoid_derivative(hiddenLayer[0].getWartosc())*inputLayer[0].getWartosc();
//				wagi_I_H[0][1] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[1] * sigmoid_derivative(hiddenLayer[1].getWartosc()) * inputLayer[0].getWartosc();
//				wagi_I_H[0][2] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[2] * sigmoid_derivative(hiddenLayer[2].getWartosc()) * inputLayer[0].getWartosc();
//
//				wagi_I_H[1][0] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[0] * sigmoid_derivative(hiddenLayer[0].getWartosc()) * inputLayer[1].getWartosc();
//				wagi_I_H[1][1] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[1] * sigmoid_derivative(hiddenLayer[1].getWartosc()) * inputLayer[1].getWartosc();
//				wagi_I_H[1][2] -= LEARNING_RATE * blad_poch * sigmoid_derivative(outputLayer.getWartosc()) * wagi_H_O[2] * sigmoid_derivative(hiddenLayer[2].getWartosc()) * inputLayer[1].getWartosc();
//
//				okno.draw(nauka);
//			}
//
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
//				//0 1
//				inputLayer[0].setWartosc(0);
//				inputLayer[1].setWartosc(1);
//
//				float x = inputLayer[0].getWartosc() * wagi_I_H[0][0] + inputLayer[1].getWartosc() * wagi_I_H[1][0] + hiddenLayer[0].getBias();
//				hiddenLayer[0].setWartosc(1 / (1 + exp(-x)));
//				x = inputLayer[0].getWartosc() * wagi_I_H[0][1] + inputLayer[1].getWartosc() * wagi_I_H[1][1] + hiddenLayer[1].getBias();
//				hiddenLayer[1].setWartosc(1 / (1 + exp(-x)));
//				x = inputLayer[0].getWartosc() * wagi_I_H[0][2] + inputLayer[1].getWartosc() * wagi_I_H[1][2] + hiddenLayer[2].getBias();
//				hiddenLayer[2].setWartosc(1 / (1 + exp(-x)));
//
//				x = hiddenLayer[0].getWartosc() * wagi_H_O[0] + hiddenLayer[1].getWartosc() * wagi_H_O[1] + hiddenLayer[2].getWartosc() * wagi_H_O[2];
//				outputLayer.setWartosc(1 / (1 + exp(-x)));
//
//				co.setString("0 1");
//				okno.draw(co);
//			}
//
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
//				//0 0
//				inputLayer[0].setWartosc(0);
//				inputLayer[1].setWartosc(0);
//
//				float x = inputLayer[0].getWartosc() * wagi_I_H[0][0] + inputLayer[1].getWartosc() * wagi_I_H[1][0] + hiddenLayer[0].getBias();
//				hiddenLayer[0].setWartosc(1 / (1 + exp(-x)));
//				x = inputLayer[0].getWartosc() * wagi_I_H[0][1] + inputLayer[1].getWartosc() * wagi_I_H[1][1] + hiddenLayer[1].getBias();
//				hiddenLayer[1].setWartosc(1 / (1 + exp(-x)));
//				x = inputLayer[0].getWartosc() * wagi_I_H[0][2] + inputLayer[1].getWartosc() * wagi_I_H[1][2] + hiddenLayer[2].getBias();
//				hiddenLayer[2].setWartosc(1 / (1 + exp(-x)));
//
//				x = hiddenLayer[0].getWartosc() * wagi_H_O[0] + hiddenLayer[1].getWartosc() * wagi_H_O[1] + hiddenLayer[2].getWartosc() * wagi_H_O[2];
//				outputLayer.setWartosc(1 / (1 + exp(-x)));
//
//				co.setString("0 0");
//				okno.draw(co);
//			}
//
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
//			//1 1
//			inputLayer[0].setWartosc(1);
//			inputLayer[1].setWartosc(1);
//
//			float x = inputLayer[0].getWartosc() * wagi_I_H[0][0] + inputLayer[1].getWartosc() * wagi_I_H[1][0] + hiddenLayer[0].getBias();
//			hiddenLayer[0].setWartosc(1 / (1 + exp(-x)));
//			x = inputLayer[0].getWartosc() * wagi_I_H[0][1] + inputLayer[1].getWartosc() * wagi_I_H[1][1] + hiddenLayer[1].getBias();
//			hiddenLayer[1].setWartosc(1 / (1 + exp(-x)));
//			x = inputLayer[0].getWartosc() * wagi_I_H[0][2] + inputLayer[1].getWartosc() * wagi_I_H[1][2] + hiddenLayer[2].getBias();
//			hiddenLayer[2].setWartosc(1 / (1 + exp(-x)));
//
//			x = hiddenLayer[0].getWartosc() * wagi_H_O[0] + hiddenLayer[1].getWartosc() * wagi_H_O[1] + hiddenLayer[2].getWartosc() * wagi_H_O[2];
//			outputLayer.setWartosc(1 / (1 + exp(-x)));
//
//			co.setString("1 1");
//			okno.draw(co);
//			}
//
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
//			//1 0
//			inputLayer[0].setWartosc(1);
//			inputLayer[1].setWartosc(0);
//
//			float x = inputLayer[0].getWartosc() * wagi_I_H[0][0] + inputLayer[1].getWartosc() * wagi_I_H[1][0] + hiddenLayer[0].getBias();
//			hiddenLayer[0].setWartosc(1 / (1 + exp(-x)));
//			x = inputLayer[0].getWartosc() * wagi_I_H[0][1] + inputLayer[1].getWartosc() * wagi_I_H[1][1] + hiddenLayer[1].getBias();
//			hiddenLayer[1].setWartosc(1 / (1 + exp(-x)));
//			x = inputLayer[0].getWartosc() * wagi_I_H[0][2] + inputLayer[1].getWartosc() * wagi_I_H[1][2] + hiddenLayer[2].getBias();
//			hiddenLayer[2].setWartosc(1 / (1 + exp(-x)));
//
//			x = hiddenLayer[0].getWartosc() * wagi_H_O[0] + hiddenLayer[1].getWartosc() * wagi_H_O[1] + hiddenLayer[2].getWartosc() * wagi_H_O[2];
//			outputLayer.setWartosc(1 / (1 + exp(-x)));
//
//			co.setString("1 0");
//			okno.draw(co);
//			}
//			zegarek.restart();
//		}
//
//
//		okno.draw(outputs_sprite);
//		inputLayer[0].draw(okno);
//		inputLayer[1].draw(okno);
//		hiddenLayer[0].draw(okno);
//		hiddenLayer[1].draw(okno);
//		hiddenLayer[2].draw(okno);
//		outputLayer.draw(okno);
//		okno.draw(xored);
//		okno.draw(inlayer);
//		okno.draw(outlayer);
//		okno.draw(hidlayer);
//		okno.display();
//		okno.clear();
//
//	}
//
//
//}
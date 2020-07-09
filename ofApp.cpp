#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2);
	ofRotateX(ofGetFrameNum() * 1.54);

	this->draw_sphere(glm::vec3(), 300);

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_sphere(glm::vec3 location, float radius) {

	vector<glm::vec3> location_list = {
		location + glm::vec3(-radius * 0.5, -radius * 0.5, radius * 0.5),
		location + glm::vec3(-radius * 0.5, radius * 0.5, radius * 0.5),
		location + glm::vec3(radius * 0.5, radius * 0.5, radius * 0.5),
		location + glm::vec3(radius * 0.5, -radius * 0.5, radius * 0.5),
		location + glm::vec3(-radius * 0.5, -radius * 0.5, -radius * 0.5),
		location + glm::vec3(-radius * 0.5, radius * 0.5, -radius * 0.5),
		location + glm::vec3(radius * 0.5, radius * 0.5, -radius * 0.5),
		location + glm::vec3(radius * 0.5, -radius * 0.5, -radius * 0.5)
	};

	if (radius < 50) {

		for (auto& l : location_list) {

			auto noise_value = ofNoise(glm::vec4(l * 0.05, ofGetFrameNum() * 0.003));

			if (noise_value < 0.85) {

				ofSetColor(ofMap(ofNoise(l * 0.05), 0, 1, 39, 239));
				ofDrawSphere(l, radius * 0.5);
			}
		}
	}
	else {

		for (auto& l : location_list) {

			auto noise_value = ofNoise(glm::vec4(l * 0.05, ofGetFrameNum() * 0.003));

			if (radius == 300 || noise_value < 0.5) {

				this->draw_sphere(l, radius * 0.5);
			}
			else if (noise_value < 0.70) {

				ofSetColor(ofMap(ofNoise(l * 0.05), 0, 1, 39, 239));
				ofDrawSphere(l, radius * 0.5);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
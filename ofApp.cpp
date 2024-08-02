#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(200, 4);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	this->frame.clear();

	for (int i = 0; i < this->triangle_list.size(); i++) {

		glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.y * 0.01, avg.x * 0.01, avg.z * 0.01, ofGetFrameNum() * 0.01);

		if (noise_value < 0.4 || noise_value > 0.6) { continue; }

		vector<glm::vec3> vertices;

		vertices.push_back(this->triangle_list[i].getVertex(0));
		vertices.push_back(this->triangle_list[i].getVertex(1));
		vertices.push_back(this->triangle_list[i].getVertex(2));

		this->mesh.addVertices(vertices);
		this->frame.addVertices(vertices);

		ofColor color;
		color.setHsb((int)(ofMap(ofNoise(glm::vec3(avg * 0.01)), 0, 1, ofGetFrameNum() * 2, (ofGetFrameNum() * 2) + 92)) % 255, 130, 255);

		for (int k = 0; k < vertices.size(); k++) {

			this->mesh.addColor(ofColor(color, 32));
			this->frame.addColor(color);
		}

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
		this->frame.addTriangle(this->frame.getNumVertices() - 1, this->frame.getNumVertices() - 2, this->frame.getNumVertices() - 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.35);

	this->mesh.draw();
	this->frame.drawWireframe();	

	this->cam.end();

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
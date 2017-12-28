
#include "Function.h"
#include <cmath>
#include <iostream>

Function::Function(int _id, string _name) {
    this->id = _id;
    this->name = _name;
}

void Function::addInput(Variable *input) {
    inputs.push_back(input);
}

void Function::setOutput(Variable *_output) {
    this->output = _output;
}

vector<Node *> Function::getIncomings() {
    vector<Node *> incomes;
    for(int i=0; i<inputs.size(); i++){
        Node* temp_in = inputs[i];
        incomes.push_back(temp_in);
    }

    return incomes;
}

vector<Node *> Function::getOutgoings() {
    vector<Node*> outgoes;
    Node* temp_out = output;
    outgoes.push_back(temp_out);
    return outgoes;
}




Multiplication::Multiplication(int _id, string _name) : Function(_id, _name) {

    this->id = _id;
    this->name = _name;

}

void Multiplication::doForward() {


    double outputVal;
    outputVal = inputs[0]->value * inputs[1]->value;



    this->output->value = outputVal;

}

void Multiplication::doBackward() {
    inputs[0]->derivative += inputs[1]->value * output->derivative;
    inputs[1]->derivative += inputs[0]->value * output->derivative;

}

Addition::Addition(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name =_name;
}

void Addition::doForward() {
    this->output->value =  inputs[0]->value + inputs[1]->value;
}

void Addition::doBackward() {

    inputs[0]->derivative += 1*output->derivative;
    inputs[1]->derivative += 1*output->derivative;
}

Sine::Sine(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void Sine::doForward() {


    this->output->value = sin(inputs[0]->value);
}

void Sine::doBackward() {

    inputs[0]->derivative += cos(inputs[0]->value)*output->derivative;
}

Cosine::Cosine(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;

}

void Cosine::doForward() {


    this->output->value = cos(inputs[0]->value);
}

void Cosine::doBackward() {

    inputs[0]->derivative += -sin(inputs[0]->value)*output->derivative;
}

Division::Division(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}
void Division::doForward() {



    this->output->value =inputs[0]->value / inputs[1]->value;
}

void Division::doBackward() {

    inputs[0]->derivative += (1/inputs[1]->value)*output->derivative;
    inputs[1]->derivative += (-inputs[0]->value/(pow(inputs[1]->value,2)))*output->derivative;
}

Subtraction::Subtraction(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}


void Subtraction::doForward() {



    this->output->value =inputs[0]->value - inputs[1]->value;
}

void Subtraction::doBackward() {

    inputs[0]->derivative += 1*output->derivative;
    inputs[1]->derivative += -1*output->derivative;
}

Tangent::Tangent(int _id, string _name) : Function(_id, _name) {
    this->name = _name;
    this->id = _id;
}

void Tangent::doForward() {


    this->output->value = tan(inputs[0]->value);
}

void Tangent::doBackward() {
    inputs[0]->derivative += (1 + pow(tan(inputs[0]->value),2))*output->derivative;
}


ArcCosine::ArcCosine(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void ArcCosine::doForward() {


    this->output->value =  acos(inputs[0]->value);
}

void ArcCosine::doBackward() {

    inputs[0]->derivative += (-1/sqrt(1-pow(inputs[0]->value,2)))*output->derivative;
}

ArcSine::ArcSine(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;

}


void ArcSine ::doForward() {


    this->output->value = asin(inputs[0]->value);
}

void ArcSine::doBackward() {

    inputs[0]->derivative += (1/sqrt(1-pow(inputs[0]->value,2)))*output->derivative;
}

ArcTangent::ArcTangent(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name= _name;
}

void ArcTangent::doForward() {


    this->output->value = atan(inputs[0]->value);
}

void ArcTangent::doBackward() {

    inputs[0]->derivative += (1/(1+pow(inputs[0]->value, 2)))*output->derivative;
}

Exponential::Exponential(int _id, string _name) : Function(_id, _name) {
    this->name = _name;
    this->id = _id;
}

void Exponential::doForward() {


    this->output->value = exp(inputs[0]->value);
}

void Exponential::doBackward() {

    inputs[0]->derivative += exp(inputs[0]->value)*output->derivative;
}

Log::Log(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void Log::doForward() {

    this->output->value = log(inputs[0]->value);
}

void Log::doBackward() {

    inputs[0]->derivative += (1/inputs[0]->value)*output->derivative;
}

Log10::Log10(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void Log10::doForward() {

    this->output->value = log10(inputs[0]->value);
}

void Log10::doBackward() {

    inputs[0]->derivative += (1/(log(10)*inputs[0]->value))*output->derivative;

}

Power::Power(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void Power::doForward() {



    this->output->value = pow(inputs[0]->value , inputs[1]->value);
}

void Power::doBackward() {

    inputs[0]->derivative += (inputs[1]->value*pow(inputs[0]->value,inputs[1]->value-1))*output->derivative;
    inputs[1]->derivative += (pow(inputs[0]->value, inputs[1]->value)*log(inputs[0]->value))*output->derivative;

}

Sqrt::Sqrt(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void Sqrt::doForward() {

    this->output->value = sqrt(inputs[0]->value);
}

void Sqrt::doBackward() {

    inputs[0]->derivative = (output->derivative/2) / sqrt(inputs[0]->value);
}


Identity::Identity(int _id, string _name) : Function(_id, _name) {
    this->id = _id;
    this->name = _name;
}

void Identity::doForward() {

    this->output->value = inputs[0]->value;
}

void Identity::doBackward() {

    inputs[0]->derivative = this->output->derivative;
}


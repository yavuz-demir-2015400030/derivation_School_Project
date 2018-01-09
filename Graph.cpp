#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Graph.h"
#include <cmath>
#include <iomanip>
#include <list>
#include <iterator>

using namespace std;

Graph::Graph() {

}

// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    // printf("%s -> %d\n",inp.c_str(), res);
//    cout<< inp << " id is  " << id[inp] << endl;
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    // cout << "new Function: " << fnc << endl;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);
    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fId = getFunction(fnc);
    int inp1Id = getVariable(inp1);
    int inp2Id = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inp1Id]);
    fncs[fId]->addInput(vars[inp2Id]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inp1Id]->addTo(fncs[fId]);
    vars[inp2Id]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}


bool Graph::isCyclic(){


}

double Graph::forwardPass(vector<double> inputValues){

    queue<int> q_Forward;

//    cout<< "start" << endl;


    for(int i=0; i<inputNodes.size(); i++){

        vars[inputNodes[i]]->value = inputValues[i];
        q_Forward.push(inputNodes[i]);
    }


//    cout<< "" << endl;

    while(!q_Forward.empty()){
        int id = q_Forward.front();
        q_Forward.pop();


//        cout<< id << endl;
        if(type[id] == VARIABLE){

            for(int i=0; i<vars[id]->getOutgoings().size(); i++){
                if(!vars[id]->getOutgoings()[i]->visited) {
                    vars[id]->getOutgoings()[i]->visited = true;
                    if(vars[id]->getOutgoings().size() == 1){
                    q_Forward.push(vars[id]->getOutgoings()[i]->id);
                    }
                    }else{
                    if(vars[id]->getOutgoings().size() == 2){
                        q_Forward.push(vars[id]->getOutgoings()[i]->id);
                    }
                }
            }

        }else{

            fncs[id]->doForward();

            vars[fncs[id]->getOutgoings()[0]->id]->value = fncs[id]->output->value;

            fncs[id]->getOutgoings()[0]->visited = true;
            q_Forward.push(fncs[id]->getOutgoings()[0]->id);
        }
    }


    for(int i=1; i<idCount+1; i++){
        if(type[i] == VARIABLE){
            vars[i]->visited = false;
        }else{
            fncs[i]->visited = false;
        }
    }

    return vars[outputNode]->value;



}

vector<double> Graph::backwardPass(){

    vars[outputNode]->derivative = 1;

    queue<int> q_Backward;

    q_Backward.push(outputNode);


    while(q_Backward.size() != 0){
        int id = q_Backward.front();
        q_Backward.pop();


        if(type[id] == VARIABLE){

            if(!vars[id]->isRoot){
                fncs[vars[id]->from->id]->visited= true;
                q_Backward.push(vars[id]->from->id);
            }

        }else{
            fncs[id]->doBackward();
            for(int i=0; i<fncs[id]->getIncomings().size(); i++){
                if(!fncs[id]->getIncomings()[i]->visited){
                    vars[fncs[id]->getIncomings()[i]->id]->visited = true;
                    q_Backward.push(fncs[id]->getIncomings()[i]->id);
                }
            }
        }
    }

    vector<double> outputDer;
    for(int i=0; i<inputNodes.size(); i++){
        outputDer.push_back(vars[inputNodes[i]]->derivative);
    }

    for(int i=1; i<idCount+1; i++){
        if(type[i] == VARIABLE){
            vars[i]->visited = false;
            vars[i]->derivative = 0;
        }else{
            fncs[i]->visited = false;
        }
    }

    return outputDer;


};


void Graph::addInput(int id) {
    inputNodes.push_back(id);
}

void Graph::setOutputNode(int id) {
    this->outputNode = id;
}

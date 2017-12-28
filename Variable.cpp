

#include "Variable.h"
#include "Function.h"

Variable::Variable() {
}

Variable::Variable(int _id, string _name, double _value) {
    this->id = _id;
    this->name = _name;
    this->value = _value;
    this->isRoot = true;
}

void Variable::setFrom(Function *_from) {
    this->from = _from;
    isRoot = false;
}

void Variable::addTo(Function *_to) {
    to.push_back(_to);
}

vector<Node *> Variable::getIncomings() {

    vector<Node*> incomes;

    Node* node_in = from;
    incomes.push_back(node_in);

    return incomes;
}

vector<Node *> Variable::getOutgoings() {

    vector<Node*> outgoes;

    for(int i=0; i<to.size(); i++){
        Node* node_out = to[i];
        outgoes.push_back(node_out);
    }
    return outgoes;

}


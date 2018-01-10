#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {


//    ifstream exp("C:\\Users\\Yavuz\\CLionProjects\\project4-yavuz-demir-2015400030-master\\exp");

    if (argc != 5) {
//        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

//    cout << "input file: " << argv[1] << endl;
//    cout << "output file: " << argv[2] << endl;

    ifstream exp(argv[1]);

    Graph myGraph;

    string temp;

    exp >> temp;
    int numOfVar=0;

    while(temp.compare("output")!=0){
        string tempVal;
        exp >> tempVal;
        myGraph.getVariable(tempVal);
        exp >> temp;
        numOfVar++;
//        cout << temp << " * " << tempVal<< endl;
    }

    string output;

    exp >> output;
    myGraph.getVariable(output);
    myGraph.setOutputNode(myGraph.getVariable(output));



    while(exp.good()) {
        exp >> temp;
        string eq,  tempF;
        myGraph.getVariable(temp);
        exp >>eq>> tempF;
        if (tempF.compare("mult") == 0) {
            string  inp1, inp2;
            exp  >> inp1 >> inp2;
            myGraph.addBinaryFunction("mult", inp1, inp2, temp);
        } else if (tempF.compare("add") == 0) {
            string  inp1, inp2;
            exp  >> inp1 >> inp2;
            myGraph.addBinaryFunction("add", inp1, inp2, temp);
        }else if(tempF.compare("subs")==0) {
            string  inp1, inp2;
            exp>> inp1 >> inp2;
            myGraph.addBinaryFunction("subs", inp1, inp2, temp);
        }else if(tempF.compare("divide")==0) {
            string  inp1, inp2;
            exp >> inp1 >> inp2;
            myGraph.addBinaryFunction("divide", inp1, inp2, temp);
        }else if(tempF.compare("sin")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("sin", inp1, temp);
        }else if(tempF.compare("cos")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("cos", inp1, temp);

        }else if(tempF.compare("identity")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("identity", inp1, temp);
        }else if(tempF.compare("tan")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("tan", inp1, temp);
        }else if(tempF.compare("acos")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("acos", inp1, temp);
        }else if(tempF.compare("asin")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("asin", inp1, temp);
        }else if(tempF.compare("atan")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("atan", inp1, temp);
        }else if(tempF.compare("exp")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("exp", inp1, temp);
        }else if(tempF.compare("log")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("log", inp1, temp);
        }else if(tempF.compare("log10")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("log10", inp1, temp);
        }else if(tempF.compare("pow")==0) {
            string  inp1, inp2;
            exp  >> inp1 >> inp2;
            myGraph.addBinaryFunction("pow", inp1, inp2, temp);
        }else if(tempF.compare("sqrt")==0) {
            string inp1;
            exp >> inp1;
            myGraph.addUnaryFunction("sqrt", inp1, temp);
        }

    }



//    ifstream input("C:\\Users\\Yavuz\\CLionProjects\\project4-yavuz-demir-2015400030-master\\input");


    ifstream input(argv[2]);


    ofstream output1, output2;
    output1.open(argv[3]);
    output2.open(argv[4]);

    vector<double> inputs;

    output1 << output << endl;

    for(int i=0; i<numOfVar; i++){
        string inp;
        input>> inp;
        myGraph.addInput(myGraph.getVariable(inp));
        output2 << "d" << output << "/d" << inp << " ";

    }
    output2 << "" << endl;

//    cout<< "\n" << endl;


        while (input.good()) {

            for (int j = 0; j < numOfVar; j++) {
                double a;
                input >> a;
              
//                cout<<setprecision(16) << a << "  ";
                inputs.push_back(a);
            }
            
//            cout << "" << endl;
//            cout << setprecision(16) << myGraph.forwardPass(inputs) << endl;
            output1 << fixed << setprecision(10) << myGraph.forwardPass(inputs)<<endl;;

            vector<double> outDer = myGraph.backwardPass();
            for (int k = 0; k < numOfVar; k++) {
//                cout << fixed << setprecision(16) << outDer[k] << "  ";
                output2 << fixed << setprecision(10) << outDer[k] << " ";
            }
            output2 << "" << endl;

            for (int j = 0; j < numOfVar; j++) {
                inputs.pop_back();
            }
        }




    return 0;
}

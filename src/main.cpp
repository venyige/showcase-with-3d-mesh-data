#include<iostream>
#include<getopt.h>
#include<Eigen/Dense>
#include<util.h>
#include<mesh.h>
#include<read_obj.h>
#include<write_stl.h>
#include<map>
#include<deque>

using namespace std;
//using namespace Eigen;
void help() {
    cout <<  "Triangular Mesh Converter \"tcmu\" - Shapr3D Homework /GoDraw"<< endl;
    cout <<  "Usage: tmcu [options] <input file with full path>" << endl;
    cout <<  "Options/Arguments:" << endl;
    cout <<  "   -h          Display this help text" << endl << endl;
    cout <<  "   -f format   The destination file format. If not given, extracted from \"-o\"."<< endl;
    cout <<  "               Formats, case insensitve: STL, OBJ, FBX, COLLADA, 3DS, IGES, STEP, X3D." << endl << endl;
    cout <<  "   -o fullpath    Write the output image to the file \"fullpath\". If not given," << endl;
    cout <<  "               output file is deduced from input file + format ( \"-f\")."<< endl<< endl;
    cout <<  "   -p pt3d     This parameter argument has to be put in between quotation marks!" << endl;
    cout <<  "               Point to investigate if included in the imported 3d body" << endl;
    cout <<  "               the coordinates are x y z, delimited with spaces, e.g. -p \"2.43 .2 0\"." << endl <<endl;
    cout <<  "   -T transforms    This parameter argument has to be put in between quotation marks!" << endl;
    cout <<  "               Transformations to be performed on the content of the input," << endl;
    cout <<  "               before being written to the output file. To be given as space separated list" << endl;
    cout <<  "               of \",\" separated command lists, as follows:" << endl;
    cout <<  "               \"cmd1,vec1,num1 cmd2,vec2,num2 ...etc.\", where cmdN is either of:" << endl;
    cout <<  "               [scal, tran, rot] for two-part scaling, translation and rotation around" << endl;
    cout <<  "               given axis, vecN is a 3D vector given as a semicolon delimited list of 3 " << endl;
    cout <<  "               decimal number, numN is a decimal value. For \"scal\" the vector holds the" << endl;
    cout <<  "               factors of non-uniform scaling, and the scalar number is for uniform scaling." << endl;
    cout <<  "               Warning: the product of the vector and scalar scale factors is to take effect." << endl;
    cout <<  "               For \"rot\" the vector is the  axis of rotation, not necessary to be" << endl;
    cout <<  "               unit (normalized). The scalar value is for the rotation angle in degrees. " << endl;
    cout <<  "               For \"tran\" translation the numN scalar value is omitted. Example:" << endl;
    cout <<  "               -T \"tran,2.22;14.12;.2,3 rot,14;15.55;1.6,25 scal,1;1;1,3\"" << endl;
}

int main(int argc, char** argv)
{
    int c;
    string inFile, ptString;
    vector<string> trStringVec;

    vector<Eigen::Vector3d> vertEV;
    vector<array<int, 3>> facV;

    std::map<int, std::string> params;

    optind = 1;

    while ((c = getopt(argc, argv, "f:o:p:T:h")) != -1) {
        switch (c) {
        case 'f':
            params[c] = optarg;
            break;
        case 'o':
            params[c] = optarg;
            break;
        case 'p':
            params[c] = optarg;
            break;
        case 'T':
            params[c] = optarg;
            break;
        case 'h':
        default:
            help();
            return 0;
        }
    }
    //    cout<<" f: "<<params['f']<<" o: "<<params['o']<<" p: "<<params['p']<<" T: "<<params['T']<<endl;
    inFile=argv[optind];
    if(basereader::chkFile(inFile)){
        //        cout<<"File is OK!"<<endl;
        //#########################################################
        //  Processing the Mesh data based on the given parameters:
        //  1. file reading, preprocessing
        //  2. class instantiating
        //    -reader
        //    -mesh
        //    -writer
        //
        //#########################################################
        read_obj objReader(inFile);
        objReader.getGeom(vertEV, facV);
        if(vertEV.size()&&facV.size()){
            mesh meshUtil(vertEV, vector<Vector3d>(), vector<Vector3d>(),  facV);
            if(!(params['f'].empty()&&params['o'].empty())){
                string fExt;
                bool gotOutFile=false;
                if(!params['o'].empty()){
                    gotOutFile=true;
                    fExt=params['o'].substr(params['o'].find_last_of(".")+1);
                    std::transform(fExt.begin(), fExt.end(), fExt.begin(),
                                   [](unsigned char c){ return std::tolower(c); });
                }
                if(!params['f'].empty()){
                    std::transform(params['f'].begin(), params['f'].end(), params['f'].begin(),
                            [](unsigned char c){ return std::tolower(c); });
                    if(!gotOutFile){
                        fExt=params['f'];
                        params['o']=inFile.substr(0, inFile.find_last_of(".")+1).append(fExt);
                        cout<<"Output file: "<<params['o']<<endl;
                    }
                }else{
                    params['f']=fExt;
                }
                if(fExt.compare(params['f'])){
                    cout<<"CONVERSION FORMAT AMBIGUITY"<<fExt<<params['f']<<endl;
                    help();
                    cout<<"The output file extension contradicts with the conversion format parameter"<<endl;
                    return 0;
                }
                ///// TEMPORARY until conversion format routines implemented
                ///
                if(params['f'].compare("stl")){
                    cout << "To "<<params['f']<<" file conversion is not yet implemented."<<endl;
                    cout<<"Please try again with \"STL\"."<<endl;
                    return 0;
                }
                /////EO TEMPORARY
                if(!params['T'].empty()){
                    vector<string> transItems=basereader::strSplit(params['T'], " ");
                    std::deque<util::trPar> trPars;
                    vector<string> triiS;
                    util::trPar triiSV;
                    vector<string> triiSN;
                    // Now, the transformation steps has to be recorded in reverse order -> std::deque
                    //                cout<<params['T']<<endl;
                    //               tran,2;2;2.3,0  rot,1;1;11.5,23.5 scal,1;1;1,3
                    for(auto trii: transItems){
                        triiS=basereader::strSplit(trii, ",");
                        triiSN=basereader::strSplit(triiS[1], ";");
                        triiSV.cmd=triiS[0];
                        triiSV.vec[0]=stod(triiSN[0]);
                        triiSV.vec[1]=stod(triiSN[1]);
                        triiSV.vec[2]=stod(triiSN[2]);
                        triiSV.num=stod(triiS[2]);
                        trPars.push_front(triiSV);
                    }
                    for(auto trii: trPars){
                        switch (trii.cmd[0]) {
                        case 't':
                            meshUtil.addTranslation(trii.vec);
                            break;
                        case 'r':
                            meshUtil.addRotation(trii.num,trii.vec);
                            break;
                        case 's':
                            meshUtil.addScaling(trii.vec*trii.num);
                            break;
                        }
                    }
                    meshUtil.performTransforms();
                }else{
                    cout<<"There is no transformation assigned through the command-line parameter\"T\""<<endl;
                }


            }else {
                cout<<"MISSING CONVERSION PARAMETER "<<endl;
                help();
                cout<<"Neither format, nor output file name has been given!"<<endl;

                return 0;
            }
            write_stl stlWriter(params['o'],
                    make_shared<vector<Eigen::Vector3d>>( meshUtil.v()),
                    make_shared<vector<array<int, 3>>>(meshUtil.f()));
            stlWriter.dumpFile();
        }else {
            cout<< "The input file does not contain vertex or face data!" <<endl;
            return 0;
        }
        /*      // Test geom data
        cout<<"vertV size:"<<vertEV.size()<<endl;
        for_each(vertEV.begin(), vertEV.end(), [](const Eigen::Vector3d& n) { std::cout << "x:" << n.x()<<" y:"<<n.y()<<" z:"<<n.z()<<endl; });
        cout<<"faceV size:"<<facV.size()<<endl;
        for_each(facV.begin(), facV.end(), [](const array<int,3>& n) { std::cout << "1:" << n[0]<<" 2:"<<n[1]<<" 3:"<<n[2]<<endl; });*/

    }else{
        cout<< "INPUT FILE PROBLEM"<<endl;
        help();
        cout<< "Input file is not accessible!"<<endl;
        return 0;
    }
    //std::unique_ptr<>
    //std::unique_ptr<mesh<>> theMesh=std::make_unique<mesh>(new mesh());
    //getchar();
    return 0;
}

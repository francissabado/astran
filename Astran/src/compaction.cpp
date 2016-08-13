/**
   \file compaction.cpp
   Compact layout.
   \date 25-sep-2006 \author Cristiano Lazzari <clazz@inf.ufrgs.br>
 */



#include "compaction.h"

/** Constructor. */
Compaction::Compaction( cp_algo a,string name) {
        algo = a;
        lp_filename = name;
        variables.clear();
        constraints.clear();
}

string Compaction::getLPName(){
        return lp_filename;
}

void Compaction::setLPName(string lp_Name){
        lp_filename = lp_Name;
}

/** Insert new variable. */
void Compaction::insertVal( string name ) {
        variables[name] = 0;
        cout << "INS VAR " << name << endl;
}

/** Insert new constraint. */
void Compaction::insertConstraintBTZ( string v1 ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.end();
        cpc.t  = variables.end();

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        cpc.type = CP_BIG_ZERO;

        constraints.push_back( cpc );
}

void Compaction::insertConstraint( string v1 ) {
        ctrts.push_back(v1);
}

/** Insert new constraint. */
void Compaction::insertConstraintEBTZ( string v1 ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.end();
        cpc.t  = variables.end();

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        cpc.type = CP_BIG_EQ_ZERO;

        constraints.push_back( cpc );
}

/** Insert new constraint. */
void Compaction::insertConstraintEZ( string v1 ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.end();
        cpc.t  = variables.end();

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        cpc.type = CP_EQ_ZERO;

        constraints.push_back( cpc );
}


/** Insert new constraint. */
void Compaction::insertConstraint( string v1, string v2, cp_cons_tp type, int val ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.find( v2 );
        cpc.t  = variables.end();

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                //    variables[v1] = 0;
                cpc.v1 = variables.find( v1 );
        }

        if ( cpc.v2 == variables.end() ) {
                insertVal( v2 );
                //    variables[v2] = 0;
                cpc.v2 = variables.find( v2 );
        }

        cpc.type = type;
        cpc.val = val;

        constraints.push_back( cpc );

}

/** Insert new constraint. */
void Compaction::insertConstraint( string v1, string v2, cp_cons_tp type, string t ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.find( v2 );
        cpc.t  = variables.find( t );

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        if ( cpc.v2 == variables.end() ) {
                insertVal( v2 );
                cpc.v2 = variables.find( v2 );
        }
        if ( cpc.t == variables.end() ) {
                insertVal( t );
                cpc.t = variables.find( t );
        }

        if ( type == CP_EQ )
                cpc.type = CP_EQ_VAR;
        else if ( type == CP_MIN )
                cpc.type = CP_MIN_VAR;
        else if ( type == CP_MAX )
                cpc.type = CP_MAX_VAR;
        else
                cpc.type = type;

        constraints.push_back( cpc );
}

/** Insert new constraint. */
void Compaction::insertConstraint( string v1, string v2, cp_cons_tp type, string t, int val ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.find( v2 );
        cpc.t  = variables.find( t );

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        if ( cpc.v2 == variables.end() ) {
                insertVal( v2 );
                cpc.v2 = variables.find( v2 );
        }
        if ( cpc.t == variables.end() ) {
                insertVal( t );
                cpc.t = variables.find( t );
        }

        if ( type == CP_EQ )
                cpc.type = CP_EQ_VAR_VAL;
        else if ( type == CP_MIN )
                cpc.type = CP_MIN_VAR_VAL;
        else if ( type == CP_MAX )
                cpc.type = CP_MAX_VAR_VAL;
        else
                cpc.type = type;

        cpc.val = val;

        constraints.push_back( cpc );
}

/** Insert Upper Bound. */
void Compaction::insertUpperBound( string v1, int val ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.end();
        cpc.t  = variables.end();

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        cpc.type = CP_UPPER_BOUND;
        cpc.val = val;

        constraints.push_back( cpc );
}

/** Insert Upper Bound. */
void Compaction::insertLowerBound( string v1, int val ) {

        cp_constraint cpc;

        cpc.v1 = variables.find( v1 );
        cpc.v2 = variables.end();
        cpc.t  = variables.end();

        if ( cpc.v1 == variables.end() ) {
                insertVal( v1 );
                cpc.v1 = variables.find( v1 );
        }

        cpc.type = CP_LOWER_BOUND;
        cpc.val = val;

        constraints.push_back( cpc );
}

/** Force these variavles to be integer. */
void Compaction::forceIntegerVar( string v ) {
        int_vars.push_back( v );
}

/** Force these variavles to be binary. */
void Compaction::forceBinaryVar( string v ) {
        bin_vars.push_back( v );
}

/** Force these variavles to be semi-continuous (0 or interval). */
void Compaction::forceSecVar( string v ) {
        sec_vars.push_back( v );
}

/** Force these variavles to be special ordered set. */
void Compaction::forceSOS( string v ) {
        sos_vars.push_back( v );
}


/** Insert LP variable. These variables are include in the minimization objective function. */
void Compaction::insertLPMinVar( string v ) {
        lp_min_var.push_back( v );
        lp_min_val.push_back( 1 );
}

/** Insert LP variable. These variables are include in the minimization objective function. */
void Compaction::insertLPMinVar( string v, int i ) {
        lp_min_var.push_back( v );
        lp_min_val.push_back( i );
}

/*
   int Compaction::solve(string lpSolverFile) {
   cout << "-> Calling LP Solver ("
   << variables.size() << " variables, "
   << constraints.size() << " constraints)" << endl;

   string fn = lp_filename + ".lp";
   ofstream f(fn.c_str());


   if ( !f ) {
   cerr << "ERROR:Cannot create file " << fn << ". Please verify your temporary directory." << endl;
   exit(-1);
   }

   f << "min: ";
   for ( unsigned int i = 0; i < lp_min_var.size(); i++ ) {
   if ( i != 0 )
   f << " + ";
   if ( lp_min_val[i] != 1 )
   f << lp_min_val[i] << " ";

   f << lp_min_var[i];
   }
   f << ";" << endl;

   // Constant zero
   variables[ "ZERO" ] = 0;
   f << "Czero: ZERO = 0;" << endl;

   for ( unsigned int i = 0; i < constraints.size(); i++ ) {

   string v1 = constraints[i].v1->first;

   string v2  = "0";
   if ( constraints[i].v2 != variables.end() )
   v2 = constraints[i].v2->first;

   string t  = "0";
   if ( constraints[i].t != variables.end() )
   t = constraints[i].t->first;

   cp_cons_tp type = constraints[i].type;

   int val = constraints[i].val;

   if ( type == CP_MIN )
   f << "C" << i << ": " << v2 << " - " << v1 << " >= " << val << ";" << endl;
   if ( type == CP_MAX )
   f << "C" << i << ": " << v2 << " - " << v1 << " <= " << val << ";" << endl;
   else if ( type == CP_EQ )
   f << "C" << i << ": " << v2 << " - " << v1 << " = " << val << ";" << endl;
   else if ( type == CP_MIN_VAR_VAL )
   f << "C" << i << ": " << v2 << " - " << v1 << " >= " << val << " " << t << ";" << endl;
   else if ( type == CP_MAX_VAR_VAL )
   f << "C" << i << ": " << v2 << " - " << v1 << " <= " << val << " " << t << ";" << endl;
   else if ( type == CP_EQ_VAR_VAL )
   f << "C" << i << ": " << v2 << " - " << v1 << " = " << val << " " << t << ";" << endl;
   else if ( type == CP_MIN_VAR )
   f << "C" << i << ": " << v2 << " - " << v1 << " >= " << t << ";" << endl;
   else if ( type == CP_MAX_VAR )
   f << "C" << i << ": " << v2 << " - " << v1 << " <= " << t << ";" << endl;
   else if ( type == CP_EQ_VAR )
   f << "C" << i << ": " << v2 << " - " << v1 << " = " << t << ";" << endl;
   else if ( type == CP_BIG_ZERO )
   f << "C" << i << ": " << v1 << " > 0;" << endl;
   else if ( type == CP_BIG_EQ_ZERO )
   f << "C" << i << ": " << v1 << " >= 0;" << endl;
   else if ( type == CP_EQ_ZERO )
   f << "C" << i << ": " << v1 << " = 0;" << endl;
   else if ( type == CP_UPPER_BOUND )
   f << "C" << i << ": " << v1 << " <= " << val << ";" << endl;
   else if ( type == CP_LOWER_BOUND )
   f << "C" << i << ": " << v1 << " >= " << val << ";" << endl;

   }

   if ( int_vars.size() > 0 ) {
   f << "int ";
   for ( unsigned int i = 0; i < int_vars.size(); i++ ) {
   if ( i != 0 )
   f << ", ";
   f << int_vars[i];
   }
   f << ";" << endl;
   }

   if ( bin_vars.size() > 0 ) {
   f << "bin ";
   for ( unsigned int i = 0; i < bin_vars.size(); i++ ) {
   if ( i != 0 )
   f << ", ";
   f << bin_vars[i];
   }
   f << ";" << endl;
   }

   if ( sec_vars.size() > 0 ) {
   f << "sec ";
   for ( unsigned int i = 0; i < sec_vars.size(); i++ ) {
   if ( i != 0 )
   f << ", ";
   f << sec_vars[i];
   }
   f << ";" << endl;
   }

   if ( sos_vars.size() > 0 ) {
   f << "sos" << endl;
   for ( unsigned int i = 0; i < sos_vars.size(); i++ )
   f << "SOS" << i << ": " << sos_vars[i] << " <= 1;" << endl;
   }


   f.close();
   string cmd = "\"" + lpSolverFile + "\" " +  lp_filename + ".lp 2> temp.log";
   cout << "-> Running command: " << cmd << endl;

   FILE *x = _popen(cmd.c_str(), "r");

   if(x==NULL){
   cout << "-> ERROR: Problem to execute lp_solve!" << endl;
   return 0;
   }

   char str[150];
   while (fgets(str, 150, x)) {

   istringstream s(str);

   string n;
   int v;

   s >> n;
   if(n=="This"){
   cout << "-> Error executing LP Solver: " << str << endl;
   return 0;
   }
   s >> v;


   map<string,int>::iterator i = variables.find( n );
   if ( i != variables.end() ) {
   i->second = v;
   }
   }

   _pclose(x);
   return 1;
   }
 */

/** Solve Compaction constraints with linear programming. */
int Compaction::solve(string lpSolverFile, int timeLimit, string otherParams) {
        cout << "-> Calling LP Solver ("
             << variables.size() << " variables, "
             << constraints.size() << " constraints)" << endl;


        generateLPConstraints();
        // bool Compaction::generateLPConstraints()



        //Linear Programming Constraints generation
        // string fn = lp_filename + ".lp";
        // {
        //         ofstream f(fn.c_str());
        //
        //         if ( !f )
        //                 throw AstranError("Cannot create file " + fn);
        //
        //         f << "Minimize" << endl;
        //         for ( unsigned int i = 0; i < lp_min_var.size(); i++ ) {
        //                 if ( i != 0 ) {
        //                         if(lp_min_val[i]>=0)
        //                                 f << " + ";
        //                         else
        //                                 f << " - ";
        //                 }
        //                 if ( lp_min_val[i] != 1 )
        //                         f << abs(lp_min_val[i]) << " ";
        //
        //                 f << lp_min_var[i];
        //         }
        //         f << endl;
        //
        //         f << "Subject To" << endl;
        //
        //         // Constant zero
        //         variables[ "ZERO" ] = 0;
        //         f << "Czero: ZERO = 0;" << endl;
        //         unsigned int i;
        //         for (i = 0; i < constraints.size(); i++ ) {
        //
        //                 string v1 = constraints[i].v1->first;
        //
        //                 string v2  = "0";
        //                 if ( constraints[i].v2 != variables.end() )
        //                         v2 = constraints[i].v2->first;
        //
        //                 string t  = "0";
        //                 if ( constraints[i].t != variables.end() )
        //                         t = constraints[i].t->first;
        //
        //                 cp_cons_tp type = constraints[i].type;
        //
        //                 int val = constraints[i].val;
        //
        //                 if ( type == CP_MIN )
        //                         f << "C" << i << ": " << v2 << " - " << v1 << " >= " << val << endl;
        //                 if ( type == CP_MAX )
        //                         f << "C" << i << ": " << v2 << " - " << v1 << " <= " << val << endl;
        //                 else if ( type == CP_EQ)
        //                         f << "C" << i << ": " << v2 << " - " << v1 << " = " << val << endl;
        //                 else if ( type == CP_MIN_VAR_VAL )
        //                         f << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " >= 0" << endl;
        //                 else if ( type == CP_MAX_VAR_VAL )
        //                         f << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " <= 0" << endl;
        //                 else if ( type == CP_EQ_VAR_VAL )
        //                         f << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " = 0" << endl;
        //                 else if ( type == CP_MIN_VAR )
        //                         f << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " >= 0" << endl;
        //                 else if ( type == CP_MAX_VAR )
        //                         f << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " <= 0" << endl;
        //                 else if ( type == CP_EQ_VAR )
        //                         f << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " = 0" << endl;
        //                 else if ( type == CP_BIG_ZERO )
        //                         f << "C" << i << ": " << v1 << " > 0" << endl;
        //                 else if ( type == CP_BIG_EQ_ZERO )
        //                         f << "C" << i << ": " << v1 << " >= 0" << endl;
        //                 else if ( type == CP_EQ_ZERO )
        //                         f << "C" << i << ": " << v1 << " = 0" << endl;
        //                 else if ( type == CP_UPPER_BOUND )
        //                         f << "C" << i << ": " << v1 << " <= " << val << endl;
        //                 else if ( type == CP_LOWER_BOUND )
        //                         f << "C" << i << ": " << v1 << " >= " << val << endl;
        //
        //         }
        //         for ( unsigned int j = 0; j < ctrts.size(); j++ ) {
        //                 f << "C" << i+j << ": " << ctrts[j] << endl;
        //         }
        //
        //         if ( int_vars.size() > 0 ) {
        //                 f << "Generals" << endl;
        //                 for (map<string,int>::iterator it = variables.begin(); it != variables.end(); ++it) {
        //                         if ( it != variables.begin() )
        //                                 f << " ";
        //                         f << it->first;
        //                 }
        //                 f << endl;
        //         }
        //
        //         if ( bin_vars.size() > 0 ) {
        //                 f << "Binary" << endl;
        //                 for ( unsigned int i = 0; i < bin_vars.size(); i++ ) {
        //                         if ( i != 0 )
        //                                 f << " ";
        //                         f << bin_vars[i];
        //                 }
        //                 f << endl;
        //         }
        //
        //         if ( sec_vars.size() > 0 ) {
        //                 f << "Semi" << endl;
        //                 for ( unsigned int i = 0; i < sec_vars.size(); i++ ) {
        //                         if ( i != 0 )
        //                                 f << " ";
        //                         f << sec_vars[i];
        //                 }
        //                 f << endl;
        //         }
        //
        //         if ( sos_vars.size() > 0 ) {
        //                 f << "sos" << endl;
        //                 for ( unsigned int i = 0; i < sos_vars.size(); i++ )
        //                         f << "SOS" << i << ": " << sos_vars[i] << " <= 1" << endl;
        //         }
        //
        //         f.flush();
        //         f.close();
        // }


        //Solve using lpSolver
        solveLP(lpSolverFile, timeLimit, otherParams);
        //remoteSolveLP(lpSolverFile, timeLimit, otherParams);
        //Other parameters possible
        // int Compaction::solveLP(string lpSolverFile, int timeLimit, string otherParams) {

        // //Calling LP Solver
        // string solFileName = lp_filename + ".sol";
        //
        // remove(solFileName.c_str());
        //
        // string cmd = "\"" + lpSolverFile + "\" TimeLimit=" + to_string(timeLimit) + " ResultFile=" + solFileName + " " + lp_filename + ".lp";
        //
        // cout << "-> Running command: " << cmd << endl;
        //
        // FILE *x = _popen(cmd.c_str(), "r");
        //
        // if(x==NULL)
        //         throw AstranError("Problem executing: " + cmd);
        //
        // cout << "-> To interrupt earlier and get the current best solution, type in a terminal: kill -2 [gurobi process]" << endl;
        // cout << "-> * and H means new feasible solution found:";
        // cerr << " ";
        //
        // char line[150];
        // while (fgets(line, 150, x)) {
        //         istringstream s(line);
        //         string n;
        //         s >> n;
        //         if(n!="Warning:")
        //                 printf("%s",line);
        //
        //         if(n=="H" || n=="*")
        //                 cerr << n;
        //
        //         if(n=="ERROR" || n=="Time" || n=="Unable" || n=="Wrote" || n=="Optimal" || n=="Model")
        //                 cout << endl << line;
        //         if(n=="Unable" || n=="Model")
        //                 return 0;
        // }
        //
        // _pclose(x);


        //Assumes that it uses lp_filename + ".sol"
        proccessLPSol();

        // //Processing solution
        // FILE* stream = fopen(solFileName.c_str(), "r");
        //
        // if(stream==NULL)
        //         throw AstranError("Problem opening: " + solFileName);
        //
        // while (fgets(line, 150, stream)) {
        //
        //         istringstream str_Stream(line);
        //
        //         string variable;
        //         double tmp;
        //         int value;
        //
        //         str_Stream >> variable;
        //
        //         //Skip comments denoted by '#'
        //         if(variable == "#") continue;
        //
        //         str_Stream >> tmp;
        //         value = round(tmp);
        //
        //         map<string,int>::iterator currentVar = variables.find( variable );
        //         if ( currentVar != variables.end() ) {
        //                 currentVar->second = value;
        //         }
        // }
        // fclose(stream);
        //
        // return 1;
        return 1;
}


int Compaction::proccessLPSol(){
//Processing solution
        string solFileName = lp_filename + ".sol";
        FILE* stream = fopen(solFileName.c_str(), "r");

        if( stream == NULL)
                throw AstranError("Problem opening: " + solFileName);

        char line[150];
        while (fgets(line, 150, stream)) {

                istringstream str_Stream(line);

                string variable;
                double tmp;
                int value;

                str_Stream >> variable;

                //Skip comments denoted by '#'
                if(variable == "#") continue;

                str_Stream >> tmp;
                value = round(tmp);

                map<string,int>::iterator currentVar = variables.find( variable );
                if ( currentVar != variables.end() ) {
                        currentVar->second = value;
                }
        }
        fclose(stream);

        return 1;

}





//Other params must be syntax correct
int Compaction::solveLP(string lpSolverFile, int timeLimit, string otherParams) {
// bool Compaction::solveLP(){
        //Calling LP Solver
        string const solFileName = lp_filename + ".sol";

        //Create backup
        if (FILE *file = fopen(solFileName.c_str(), "r")) {
                fclose(file);
                const string newName = lp_filename + to_string(time(NULL)) + ".sol";
                std::rename(solFileName.c_str(), newName.c_str());
        }

        remove(solFileName.c_str());

        string cmd = "\"" + lpSolverFile + "\" TimeLimit=" + to_string(timeLimit) + " ResultFile=" + solFileName + " " + otherParams + " " + lp_filename + ".lp";

        cout << "-> Running command: " << cmd << endl;

        FILE *solverLog = _popen(cmd.c_str(), "r");

        if(solverLog == NULL)
                throw AstranError("Problem executing: " + cmd);

        cout << "-> To interrupt earlier and get the current best solution, type in a terminal: kill -2 [gurobi process]" << endl;
        cout << "-> * and H means new feasible solution found:";
        cerr << " ";

        char line[150];
        while (fgets(line, 150, solverLog)) {
                istringstream s(line);
                string status;
                s >> status;
                if(status!="Warning:")
                        printf("%s",line);

                if(status == "H" || status == "*")
                        cerr << status;

                if(status == "ERROR" || status == "Time" || status == "Unable" || status == "Wrote" || status == "Optimal" || status == "Model")
                        cout << endl << line;
                if(status == "Unable" || status == "Model")
                        return 0;
        }

        _pclose(solverLog);
        return 1;

}


//Other params must be syntax correct
//Assume files are already set up
int Compaction::remoteSolveLP(string lpSolverFile, int timeLimit, string otherParams) {
// bool Compaction::solveLP(){
        //Remote settingsName
        string user = "fsabado";
        string server = "digisrv2";
        string projectDir = "~/tmpGurobi";

        string const lpFileName = lp_filename + ".lp";
        string const solFileName = lp_filename + ".sol";

        //Copying setup file
        // FILE *remoteLog = _open("cp")
        //Assumes that astran is run on current directory and sshfs is set up
        // int result = system("cp ./ILPmodel.lp ~/tmpGurobi/");
        // string cpLP_cmd = "cp " + " ./" + lpFileName + " " + projectDir + "/";
        string cpLP_cmd = "cp ./" + lpFileName + " " + projectDir + "/";
        int lpCP = system(cpLP_cmd.c_str());

        //Calling LP Solver

        //Create Backup
        if (FILE *file = fopen(solFileName.c_str(), "r")) {
                fclose(file);
                const string newName = lp_filename + to_string(time(NULL)) + ".sol";
                std::rename(solFileName.c_str(), newName.c_str());
        }

        remove(solFileName.c_str());

        // ssh fsabado@digisrv2.ddns.uark.edu 'source /opt/gurobi652/setup.bash;cd /home/fsabado/Tezzaron3D_project/GDSFiles/charteredNCL;gurobi_cl TimeLimit=100 ResultFile=ILPmodel.sol ./ILPmodel.lp'

        // remove(solFileName.c_str());
        // string cmd = "\"" + lpSolverFile + "\" TimeLimit=" + to_string(timeLimit) + " ResultFile=" + solFileName + " " + otherParams + " " + lp_filename + ".lp";

        // string cmd = "ssh fsabado@digisrv2.ddns.uark.edu \'source /opt/gurobi652/setup.bash;cd /home/fsabado/tmpGurobi;gurobi_cl TimeLimit=100 ResultFile=ILPmodel.sol ./ILPmodel.lp\'";

        string sshCmd = "ssh fsabado@digisrv2.ddns.uark.edu \'source /opt/gurobi652/setup.bash;cd /home/fsabado/tmpGurobi;";
        string cmd = "\"" + lpSolverFile + "\" TimeLimit=" + to_string(timeLimit) + " ResultFile=" + solFileName + " " + otherParams + " " + lpFileName;

        cout << "-> Running command: " << sshCmd + cmd << endl;

        FILE *solverLog = _popen(cmd.c_str(), "r");


        if(solverLog == NULL)
                throw AstranError("Problem executing: " + cmd);

        cout << "-> To interrupt earlier and get the current best solution, type in a terminal: kill -2 [gurobi process]" << endl;
        cout << "-> * and H means new feasible solution found:";
        cerr << " ";

        char line[150];
        while (fgets(line, 150, solverLog)) {
                istringstream s(line);
                string status;
                s >> status;
                if(status!="Warning:")
                        printf("%s",line);

                if(status == "H" || status == "*")
                        cerr << status;

                if(status == "ERROR" || status == "Time" || status == "Unable" || status == "Wrote" || status == "Optimal" || status == "Model")
                        cout << endl << line;
                if(status == "Unable" || status == "Model")
                        return 0;
        }

        _pclose(solverLog);
        // int result1 = system("cp ~/tmpGurobi/ILPmodel.sol ./ILPmodel.sol");
        string cpSol_cmd = "cp " + projectDir + "/" + solFileName + " ./" +  solFileName;
        int solCP = system( cpSol_cmd.c_str());


        return 1;

}




//Source: http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool Compaction::isConstraintsGenerated(){
        string constraintFile = lp_filename + ".lp";
        struct stat buffer;
        return (stat (constraintFile.c_str(), &buffer) == 0);
}


/** Solve Compaction constraints with linear programming. */
//lp_filename uses .lp extension
bool Compaction::generateLPConstraints(){
        //Linear Programming Constraints generation
        string constraintFile = lp_filename + ".lp";

        ofstream fileStream(constraintFile.c_str());

        if ( !fileStream )
                throw AstranError("Cannot create file " + lp_filename);

        fileStream << "Minimize" << endl;
        for ( unsigned int i = 0; i < lp_min_var.size(); i++ ) {
                if ( i != 0 ) {
                        if(lp_min_val[i]>=0)
                                fileStream << " + ";
                        else
                                fileStream << " - ";
                }
                if ( lp_min_val[i] != 1 )
                        fileStream << abs(lp_min_val[i]) << " ";

                fileStream << lp_min_var[i];
        }
        fileStream << endl;

        fileStream << "Subject To" << endl;

        // Constant zero
        variables[ "ZERO" ] = 0;
        fileStream << "Czero: ZERO = 0;" << endl;
        unsigned int i;
        for (i = 0; i < constraints.size(); i++ ) {

                string v1 = constraints[i].v1->first;

                string v2  = "0";
                if ( constraints[i].v2 != variables.end() )
                        v2 = constraints[i].v2->first;

                string t  = "0";
                if ( constraints[i].t != variables.end() )
                        t = constraints[i].t->first;

                cp_cons_tp type = constraints[i].type;

                int val = constraints[i].val;

                if ( type == CP_MIN )
                        fileStream << "C" << i << ": " << v2 << " - " << v1 << " >= " << val << endl;
                if ( type == CP_MAX )
                        fileStream << "C" << i << ": " << v2 << " - " << v1 << " <= " << val << endl;
                else if ( type == CP_EQ)
                        fileStream << "C" << i << ": " << v2 << " - " << v1 << " = " << val << endl;
                else if ( type == CP_MIN_VAR_VAL )
                        fileStream << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " >= 0" << endl;
                else if ( type == CP_MAX_VAR_VAL )
                        fileStream << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " <= 0" << endl;
                else if ( type == CP_EQ_VAR_VAL )
                        fileStream << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " = 0" << endl;
                else if ( type == CP_MIN_VAR )
                        fileStream << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " >= 0" << endl;
                else if ( type == CP_MAX_VAR )
                        fileStream << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " <= 0" << endl;
                else if ( type == CP_EQ_VAR )
                        fileStream << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " = 0" << endl;
                else if ( type == CP_BIG_ZERO )
                        fileStream << "C" << i << ": " << v1 << " > 0" << endl;
                else if ( type == CP_BIG_EQ_ZERO )
                        fileStream << "C" << i << ": " << v1 << " >= 0" << endl;
                else if ( type == CP_EQ_ZERO )
                        fileStream << "C" << i << ": " << v1 << " = 0" << endl;
                else if ( type == CP_UPPER_BOUND )
                        fileStream << "C" << i << ": " << v1 << " <= " << val << endl;
                else if ( type == CP_LOWER_BOUND )
                        fileStream << "C" << i << ": " << v1 << " >= " << val << endl;

        }
        for ( unsigned int j = 0; j < ctrts.size(); j++ ) {
                fileStream << "C" << i+j << ": " << ctrts[j] << endl;
        }

        if ( int_vars.size() > 0 ) {
                fileStream << "Generals" << endl;
                for (map<string,int>::iterator it = variables.begin(); it != variables.end(); ++it) {
                        if ( it != variables.begin() )
                                fileStream << " ";
                        fileStream << it->first;
                }
                fileStream << endl;
        }

        if ( bin_vars.size() > 0 ) {
                fileStream << "Binary" << endl;
                for ( unsigned int i = 0; i < bin_vars.size(); i++ ) {
                        if ( i != 0 )
                                fileStream << " ";
                        fileStream << bin_vars[i];
                }
                fileStream << endl;
        }

        if ( sec_vars.size() > 0 ) {
                fileStream << "Semi" << endl;
                for ( unsigned int i = 0; i < sec_vars.size(); i++ ) {
                        if ( i != 0 )
                                fileStream << " ";
                        fileStream << sec_vars[i];
                }
                fileStream << endl;
        }

        if ( sos_vars.size() > 0 ) {
                fileStream << "sos" << endl;
                for ( unsigned int i = 0; i < sos_vars.size(); i++ )
                        fileStream << "SOS" << i << ": " << sos_vars[i] << " <= 1" << endl;
        }

        fileStream.flush();
        fileStream.close();

        return 1;

}

//
//int Compaction::solve(string lpSolverFile, int timeLimit) {
//        cout << "-> Calling LP Solver ("
//             << variables.size() << " variables, "
//             << constraints.size() << " constraints)" << endl;
//
//
//        //Linear Programming Constraints generation
//        string fn = lp_filename + ".lp";
//        {
//                ofstream f(fn.c_str());
//
//                if ( !f )
//                        throw AstranError("Cannot create file " + fn);
//
//                f << "Minimize" << endl;
//                for ( unsigned int i = 0; i < lp_min_var.size(); i++ ) {
//                        if ( i != 0 ) {
//                                if(lp_min_val[i]>=0)
//                                        f << " + ";
//                                else
//                                        f << " - ";
//                        }
//                        if ( lp_min_val[i] != 1 )
//                                f << abs(lp_min_val[i]) << " ";
//
//                        f << lp_min_var[i];
//                }
//                f << endl;
//
//                f << "Subject To" << endl;
//
//                // Constant zero
//                variables[ "ZERO" ] = 0;
//                f << "Czero: ZERO = 0;" << endl;
//                unsigned int i;
//                for (i = 0; i < constraints.size(); i++ ) {
//
//                        string v1 = constraints[i].v1->first;
//
//                        string v2  = "0";
//                        if ( constraints[i].v2 != variables.end() )
//                                v2 = constraints[i].v2->first;
//
//                        string t  = "0";
//                        if ( constraints[i].t != variables.end() )
//                                t = constraints[i].t->first;
//
//                        cp_cons_tp type = constraints[i].type;
//
//                        int val = constraints[i].val;
//
//                        if ( type == CP_MIN )
//                                f << "C" << i << ": " << v2 << " - " << v1 << " >= " << val << endl;
//                        if ( type == CP_MAX )
//                                f << "C" << i << ": " << v2 << " - " << v1 << " <= " << val << endl;
//                        else if ( type == CP_EQ)
//                                f << "C" << i << ": " << v2 << " - " << v1 << " = " << val << endl;
//                        else if ( type == CP_MIN_VAR_VAL )
//                                f << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " >= 0" << endl;
//                        else if ( type == CP_MAX_VAR_VAL )
//                                f << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " <= 0" << endl;
//                        else if ( type == CP_EQ_VAR_VAL )
//                                f << "C" << i << ": " << v2 << " - " << val << " " << t << " - " << v1 << " = 0" << endl;
//                        else if ( type == CP_MIN_VAR )
//                                f << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " >= 0" << endl;
//                        else if ( type == CP_MAX_VAR )
//                                f << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " <= 0" << endl;
//                        else if ( type == CP_EQ_VAR )
//                                f << "C" << i << ": " << v2 << " - " << v1 << " - " << t << " = 0" << endl;
//                        else if ( type == CP_BIG_ZERO )
//                                f << "C" << i << ": " << v1 << " > 0" << endl;
//                        else if ( type == CP_BIG_EQ_ZERO )
//                                f << "C" << i << ": " << v1 << " >= 0" << endl;
//                        else if ( type == CP_EQ_ZERO )
//                                f << "C" << i << ": " << v1 << " = 0" << endl;
//                        else if ( type == CP_UPPER_BOUND )
//                                f << "C" << i << ": " << v1 << " <= " << val << endl;
//                        else if ( type == CP_LOWER_BOUND )
//                                f << "C" << i << ": " << v1 << " >= " << val << endl;
//
//                }
//                for ( unsigned int j = 0; j < ctrts.size(); j++ ) {
//                        f << "C" << i+j << ": " << ctrts[j] << endl;
//                }
//
//                if ( int_vars.size() > 0 ) {
//                        f << "Generals" << endl;
//                        for (map<string,int>::iterator it = variables.begin(); it != variables.end(); ++it) {
//                                if ( it != variables.begin() )
//                                        f << " ";
//                                f << it->first;
//                        }
//                        f << endl;
//                }
//
//                if ( bin_vars.size() > 0 ) {
//                        f << "Binary" << endl;
//                        for ( unsigned int i = 0; i < bin_vars.size(); i++ ) {
//                                if ( i != 0 )
//                                        f << " ";
//                                f << bin_vars[i];
//                        }
//                        f << endl;
//                }
//
//                if ( sec_vars.size() > 0 ) {
//                        f << "Semi" << endl;
//                        for ( unsigned int i = 0; i < sec_vars.size(); i++ ) {
//                                if ( i != 0 )
//                                        f << " ";
//                                f << sec_vars[i];
//                        }
//                        f << endl;
//                }
//
//                if ( sos_vars.size() > 0 ) {
//                        f << "sos" << endl;
//                        for ( unsigned int i = 0; i < sos_vars.size(); i++ )
//                                f << "SOS" << i << ": " << sos_vars[i] << " <= 1" << endl;
//                }
//
//                f.flush();
//                f.close();
//        }
//
//
//        //Calling LP Solver
//        string solFileName = lp_filename + ".sol";
//
//        remove(solFileName.c_str());
//
//        string cmd = "\"" + lpSolverFile + "\" TimeLimit=" + to_string(timeLimit) + " ResultFile=" + solFileName + " " + lp_filename + ".lp";
//
//        cout << "-> Running command: " << cmd << endl;
//
//        FILE *x = _popen(cmd.c_str(), "r");
//
//        if(x==NULL)
//                throw AstranError("Problem executing: " + cmd);
//
//        cout << "-> To interrupt earlier and get the current best solution, type in a terminal: kill -2 [gurobi process]" << endl;
//        cout << "-> * and H means new feasible solution found:";
//        cerr << " ";
//
//        char line[150];
//        while (fgets(line, 150, x)) {
//                istringstream s(line);
//                string n;
//                s >> n;
//                if(n!="Warning:")
//                        printf("%s",line);
//
//                if(n=="H" || n=="*")
//                        cerr << n;
//
//                if(n=="ERROR" || n=="Time" || n=="Unable" || n=="Wrote" || n=="Optimal" || n=="Model")
//                        cout << endl << line;
//                if(n=="Unable" || n=="Model")
//                        return 0;
//        }
//
//        _pclose(x);
//
//
//        //Processing solution
//        FILE* stream = fopen(solFileName.c_str(), "r");
//
//        if(stream==NULL)
//                throw AstranError("Problem opening: " + solFileName);
//
//        while (fgets(line, 150, stream)) {
//
//                istringstream str_Stream(line);
//
//                string variable;
//                double tmp;
//                int value;
//
//                str_Stream >> variable;
//
//                //Skip comments denoted by '#'
//                if(variable == "#") continue;
//
//                str_Stream >> tmp;
//                value = round(tmp);
//
//                map<string,int>::iterator currentVar = variables.find( variable );
//                if ( currentVar != variables.end() ) {
//                        currentVar->second = value;
//                }
//        }
//        fclose(stream);
//
//        return 1;
//}



/** Get variables values. */
int Compaction::getVariableVal( string name ) {
        map<string,int>::iterator i = variables.find( name );
        if ( i != variables.end() )
                return i->second;
        return -1;
}

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double springCalc(double, double, double&, double);
double criticalDampCalc(double, double, double);
void reverseSpring(double&, double, double, double, double&);

//（＊＾Ｕ＾）人（≧Ｖ≦＊）/
//＼（＾○＾）人（＾○＾）／

//1-3in/s 65%
//4-17 30%

int main()
{
    double frKeff, flKeff, rrKeff, rlKeff, frontMR, rearMR, frMass, flMass, rrMass, rlMass;
    
    tomochan();
    cout << "Hello! Today we're gonna find out your perfect valving and spring rates! ≧◡≦" << endl;
    
    cout << "\nWe'll start with natural frequency to find spring rates first.\nNatural frequency is basically how stiff your car rides, based on a number usually between ~1.3 and ~2.2" << endl;
    
    char cB = 'n';
    char rS = 'n';
    double natFreqF, natFreqR;
    
    cout << "\nHave you corner balanced your car? (y/n): ";
    
    do
    {
        cin >> cB;
        
        if (cB == 'n')
            cout << "Thats okay, we can work with your stock weight distribution then ヽ(^◇^*)/" << endl;
        else if (cB == 'y')
            cout << "\n＼（＾○＾）人（＾○＾）／ Great! Your suspension will be even more dialed in!" << endl;
        else
            cout << "I'm sorry, what? (ㄒoㄒ)" << endl;
    } while (cB != 'y' && cB != 'n');
    
    if (cB == 'n')
    {
        double fDist, rDist;
        int weightD, weightC, unSprung;
        
        cout << "\nWhat is the curb weight of your car? (in kg): ";
        cin >> weightC;
        
        cout << "\nWhat is your driver weight? (for calculation purposes only ●﹏●): ";
        cin >> weightD;
        
        cout << "\nWhat is your unsprung mass? (per corner): ";
        cin >> unSprung;
        
        cout << "\nWhat is your front weight distibution (in decimal form): ";
        cin >> fDist;
        
        rDist = 1.0 - fDist;
        
        frMass = (weightD + weightC) * fDist / 2.0 - unSprung;
        flMass = frMass;
        
        rrMass = (weightD + weightC) * rDist / 2.0 - unSprung;
        rlMass = rrMass;
    }
    
    else if (cB == 'y')
    {
        cout << "\nWhat is your front right mass? (in kg): ";
        cin >> frMass;
        
        cout << "\nWhat is your front left mass? : ";
        cin >> flMass;
        
        cout << "\nWhat is your rear right mass?: ";
        cin >> rrMass;
        
        cout << "\nWhat is your rear left mass?: ";
        cin >> rlMass;
    }
    
    cout << "\nWhat is your front motion ratio?: ";
    cin >> frontMR;
    
    cout << "\nWhat is your rear motion ratio?: ";
    cin >> rearMR;
    
    cout << "\nWhat's your desired front natural frequency?: ";
    cin >> natFreqF;
    
    cout << "\nWhat's your desired rear natural frequency?: ";
    cin >> natFreqR;
    
    double frKw = springCalc(natFreqF, frMass, frKeff, frontMR);
    double flKw = springCalc(natFreqF, flMass, flKeff, frontMR);
    double rrKw = springCalc(natFreqR, rrMass, rrKeff, rearMR);
    double rlKw = springCalc(natFreqR, rlMass, rlKeff, rearMR);
    
    double frCoilCrit = criticalDampCalc(frMass, frKw, frontMR);
    double flCoilCrit = criticalDampCalc(flMass, flKw, frontMR);
    double rrCoilCrit = criticalDampCalc(rrMass, rrKw, rearMR);
    double rlCoilCrit = criticalDampCalc(rlMass, rlKw, rearMR);
    
    cout << endl << endl << setw(10) << "Corner" << setw(23) << "Spring rate (Kg/mm)" << "Critical damping force (lbs/in/s)" << endl;
    cout << left << setw(10) << "LF" << setw(23) << flKeff << flCoilCrit << endl;
    cout << left << setw(10) << "RF" << setw(23) << frKeff << frCoilCrit << endl;
    cout << left << setw(10) << "LR" << setw(23) << rlKeff << rlCoilCrit << endl;
    cout << left << setw(10) << "RR" << setw(23) << rrKeff << rrCoilCrit << endl;
    
    if (cB == 'y')
        cout << "\nThese might be all different since you corner balanced, so just pick something in the middle for the fronts and rears ^‿^" << endl;
    
    cout << "These spring rates might not be exactly available to buy (e.g. 4.3k). Would you like to reenter the closest spring rate available to get more precise damping force and natural frequency? (y/n): ";
    cin >> rS;
    
    if (rS == 'y')
    {
        cout << "\nFront right spring rate?: ";
        cin >> frKeff;
        cout << "\nFront left spring rate?: ";
        cin >> flKeff;
        cout << "\nRear right spring rate?: ";
        cin >> rrKeff;
        cout << "\nRear left spring rate?: ";
        cin >> rlKeff;
        
        reverseSpring(natFreqF, frMass, frKeff, frontMR, frKw);
        reverseSpring(natFreqF, flMass, flKeff, frontMR, flKw);
        reverseSpring(natFreqR, rrMass, rrKeff, rearMR, rrKw);
        reverseSpring(natFreqR, rlMass, rlKeff, rearMR, rlKw);
        
        double frCoilCrit = criticalDampCalc(frMass, frKw, frontMR);
        double flCoilCrit = criticalDampCalc(flMass, flKw, frontMR);
        double rrCoilCrit = criticalDampCalc(rrMass, rrKw, rearMR);
        double rlCoilCrit = criticalDampCalc(rlMass, rlKw, rearMR);
        
        cout << endl << endl << setw(10) << "Corner" << setw(23) << "Spring rate (Kg/mm)" << setw(38) << "Critical damping force (lbs/in/s)" << "Natural frequency (Hz)" << endl;
        cout << left << setw(10) << "LF" << setw(23) << flKeff << setw(38) << flCoilCrit << natFreqF << endl;
        cout << left << setw(10) << "RF" << setw(23) << frKeff << setw(38) << frCoilCrit << natFreqF << endl;
        cout << left << setw(10) << "LR" << setw(23) << rlKeff << setw(38) << rlCoilCrit << natFreqR << endl;
        cout << left << setw(10) << "RR" << setw(23) << rrKeff << setw(38) << rrCoilCrit << natFreqR << endl;
    }
}


double springCalc(double natFreq, double mass, double& keff, double MR)
{
    double Kw = ((2 * natFreq * 3.14159) * (2 * natFreq * 3.14159)) * mass;
    keff = (Kw / (MR * MR)) / 9806.65;
    
    return Kw;
}

double criticalDampCalc(double mass, double Kw, double MR)
{
    double wheelCrit = 2 * sqrt(mass * Kw);
    double critCoil = wheelCrit / (MR * MR);
    critCoil = critCoil * (2.2 / 9.806) * (1 / 39.37);
    
    return critCoil;
}

void reverseSpring(double& natFreq, double mass, double keff, double MR, double& Kw)
{
    Kw = (keff * 9806.65) * (MR * MR);
    natFreq = (1/ (2 * 3.14159)) * sqrt(Kw / mass);
}

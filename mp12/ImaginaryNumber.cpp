#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber() : Number::Number(IMAGINARY, 0, calculate_phase(0, 0)) {
    /* Your code here */
    imaginary_component = 0;
}

ImaginaryNumber::ImaginaryNumber(double rval) : Number::Number(IMAGINARY, rval, calculate_phase(0, rval)) {
    /* Your code here */
    imaginary_component = rval;
    // Fix magnitude if negative
    if (magnitude < 0) magnitude = -magnitude;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other ) {
    /* Your code here */
    number_type = other.number_type;
    magnitude = other.magnitude;
    phase = other.phase;
    imaginary_component = other.imaginary_component;
}

void ImaginaryNumber::set_imaginary_component (double rval) {
    /* Your code here */
    imaginary_component = rval;
    // set magnitude and phase
    magnitude = imaginary_component >= 0 ? imaginary_component : -imaginary_component;
    phase = calculate_phase(0, imaginary_component);
}

double ImaginaryNumber::get_imaginary_component() const {
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    /* Your code here */
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg) {
    /* Your code here */
    return ImaginaryNumber(this->imaginary_component + arg.imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg) {
    /* Your code here */
    return ImaginaryNumber(this->imaginary_component - arg.imaginary_component);
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg) {
    /* Your code here */
    return RealNumber(-(this->imaginary_component * arg.imaginary_component));
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg) {
    /* Your code here */
    return RealNumber(this->imaginary_component / arg.imaginary_component);
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg) {
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), this->imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg) {
    /* Your code here */
    return ComplexNumber(-arg.get_real_component(), this->imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg) {
    /* Your code here */
    return ImaginaryNumber(this->imaginary_component * arg.get_real_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg) {
    /* Your code here */
    return ImaginaryNumber(this->imaginary_component / arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg) {
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), this->imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg) {
    /* Your code here */
    return ComplexNumber(-(arg.get_real_component()), this->imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg) {
    /* Your code here */
    // Convert to complex for simplicity
    ComplexNumber thisComplexEquiv(0, this->imaginary_component);
    return thisComplexEquiv.operator*(arg);
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg) {
    /* Your code here */
    // Convert to complex for simplicity
    ComplexNumber thisComplexEquiv(0, this->imaginary_component);
    return thisComplexEquiv.operator/(arg);
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}
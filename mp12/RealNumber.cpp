#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber() : Number::Number(REAL, 0, calculate_phase(0, 0)) {
    /* Your code here */
    real_component = 0;
}

RealNumber::RealNumber(double rval) : Number::Number(REAL, rval, calculate_phase(rval, 0)) {
    /* Your code here */
    real_component = rval;
    // Fix magnitude if negative
    if (magnitude < 0) magnitude = -magnitude;
}

RealNumber::RealNumber( const RealNumber& other ) {
    /* Your code here */
    number_type = other.number_type;
    magnitude = other.magnitude;
    phase = other.phase;
    real_component = other.real_component;
}

void RealNumber::set_real_component (double rval) {
    /* Your code here */
    real_component = rval;
    // also set magnitude and phase
    magnitude = real_component >= 0 ? real_component : -real_component;
    phase = calculate_phase(real_component, 0);
}

double RealNumber::get_real_component() const {
    /* Your code here */
    return real_component;
}

double RealNumber::get_magnitude() const {
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg) {
    /* Your code here */
    // this pointer is not necessary but is good for code readability
    return RealNumber(this->real_component + arg.real_component);
}

RealNumber RealNumber::operator - (const RealNumber& arg) {
    /* Your code here */
    return RealNumber(this->real_component - arg.real_component);
}

RealNumber RealNumber::operator * (const RealNumber& arg) {
    /* Your code here */
    return RealNumber(this->real_component * arg.real_component);
}

RealNumber RealNumber::operator / (const RealNumber& arg) {
    /* Your code here */
    return RealNumber(this->real_component / arg.real_component);
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(this->real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(this->real_component, -(arg.get_imaginary_component()));
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(this->real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
    double denum = arg.get_imaginary_component() * arg.get_imaginary_component();
    double numerator = - (this->real_component * arg.get_imaginary_component());
	return ImaginaryNumber(numerator / denum);
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(this->real_component + arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(this->real_component - arg.get_real_component(), -(arg.get_imaginary_component()));
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(this->real_component * arg.get_real_component(), this->real_component * arg.get_real_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
    // Convert for simplicity
    ComplexNumber thisComplexEquiv(this->real_component, 0);
    return thisComplexEquiv.operator/(arg);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}
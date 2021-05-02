#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber() : Number::Number(COMPLEX, 0, calculate_phase(0, 0)) {
    /* Your code here */
    real_component = 0;
    imaginary_component = 0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component) {
    /* Your code here */
    number_type = COMPLEX;
	magnitude = sqrt( (rval_real_component*rval_real_component) + (rval_imaginary_component*rval_imaginary_component) );
	phase = calculate_phase(rval_real_component, rval_imaginary_component);
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other ) {
    /* Your code here */
    number_type = other.number_type;
	magnitude = other.magnitude;
	phase = other.phase;
    real_component = other.real_component;
    imaginary_component = other.imaginary_component;
}

void ComplexNumber::set_real_component (double rval) {
    /* Your code here */
    real_component = rval;
    // Calculate magnitude and phase
    magnitude = sqrt( (real_component*real_component) + (imaginary_component*imaginary_component) );
	phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_real_component() const {
    /* Your code here */
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval) {
    /* Your code here */
    imaginary_component = rval;
    // Calculate magnitude and phase
    magnitude = sqrt( (real_component*real_component) + (imaginary_component*imaginary_component) );
	phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_imaginary_component() const {
    /* Your code here */
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg) {
    /* Your code here */
    return ComplexNumber(this->real_component + arg.real_component, this->imaginary_component + arg.imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg) {
    /* Your code here */
    return ComplexNumber(this->real_component - arg.real_component, this->imaginary_component - arg.imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg) {
    /* Your code here */
    double multRealComponent = (this->real_component*arg.real_component) - (this->imaginary_component*arg.imaginary_component);
    double multImaginaryComponent = (this->real_component*arg.imaginary_component) + (this->imaginary_component*arg.real_component);
    return ComplexNumber(multRealComponent, multImaginaryComponent);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg) {
    /* Your code here */
    double denum = (arg.real_component * arg.real_component) + (arg.imaginary_component * arg.imaginary_component);
    double divRealComponent = ((this->real_component * arg.real_component) + (this->imaginary_component * arg.imaginary_component)) / denum; 
    double divImaginaryComponent = ((this->imaginary_component * arg.real_component)-(this->real_component * arg.imaginary_component)) / denum; 
    return ComplexNumber(divRealComponent, divImaginaryComponent);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg) {
    /* Your code here */
	return ComplexNumber(this->real_component+arg.get_real_component(), this->imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg) {
    /* Your code here */
	return ComplexNumber(this->real_component-arg.get_real_component(), this->imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg) {
    /* Your code here */
	return ComplexNumber(this->real_component*arg.get_real_component(), this->imaginary_component*arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg) {
    /* Your code here */
    // Simply convert for convenience
    ComplexNumber realNumArgEquiv(arg.get_real_component(), 0);
	return this->operator/(realNumArgEquiv);
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg) {
    /* Your code here */
	return ComplexNumber(this->real_component, this->imaginary_component+arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg) {
    /* Your code here */
	return ComplexNumber(this->real_component, this->imaginary_component-arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg) {
    /* Your code here */
    // Simply convert for convenience
    ComplexNumber imaginaryArgEquiv(0, arg.get_imaginary_component());
	return this->operator*(imaginaryArgEquiv);
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg) {
    /* Your code here */
    // Simply convert for convenience
    ComplexNumber imaginaryArgEquiv(0, arg.get_imaginary_component());
	return this->operator/(imaginaryArgEquiv);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}
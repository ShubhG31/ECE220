#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    /* Your code here */
    real_component=0;
    imaginary_component=0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    /* Your code here */
    real_component=rval_real_component;
    imaginary_component=rval_imaginary_component;
    magnitude=sqrt((rval_imaginary_component*rval_imaginary_component)+(rval_imaginary_component*rval_imaginary_component));
    phase=calculate_phase(rval_real_component,rval_imaginary_component);
    number_type=COMPLEX;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    /* Your code here */
    real_component=other.real_component;
    imaginary_component=other.imaginary_component;
    magnitude=other.magnitude;
    phase=other.phase;
    number_type=other.number_type;
}

void ComplexNumber::set_real_component (double rval)
{
    /* Your code here */
    real_component=rval;
    return;
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return 0.0;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return 0.0;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return 0.0;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return 0.0;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber();
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber();
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */

    return ComplexNumber();
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber();
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
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
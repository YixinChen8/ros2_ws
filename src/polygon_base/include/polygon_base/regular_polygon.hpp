#ifndef POLYGON_BASE_REGULAR_POLYGON_HPP
#define POLYGON_BASE_REGULAR_POLYGON_HPP

namespace polygon_base
{
//   creates an abstract class called RegularPolygon
  class RegularPolygon
  {
    public:
    // One thing to notice is the presence of the initialize method. 
    // With pluginlib, a constructor without parameters is required, 
    // so if any parameters to the class are needed, we use the initialize method to pass them to the object.
      virtual void initialize(double side_length) = 0;
      virtual double area() = 0;
      virtual ~RegularPolygon(){}

    protected:
      RegularPolygon(){}
  };
}  // namespace polygon_base

#endif  // POLYGON_BASE_REGULAR_POLYGON_HPP
// #include <cstdio>

// int main(int argc, char ** argv)
// {
//   (void) argc;
//   (void) argv;

//   printf("hello world polygon_base package\n");
//   return 0;
// }


#include <pluginlib/class_loader.hpp>
#include <polygon_base/regular_polygon.hpp>

int main(int argc, char** argv)
{
  // To avoid unused parameter warnings
  (void) argc;
  (void) argv;

  /*
  The ClassLoader is the key class to understand, defined in the class_loader.hpp header file:
  - It is templated with the base class, i.e. polygon_base::RegularPolygon.
  - The first argument is a string for the package name of the base class, i.e. polygon_base.
  - The second argument is a string with the fully qualified base class type for the plugin, i.e. polygon_base::RegularPolygon.
  */
  pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("polygon_base", "polygon_base::RegularPolygon");

  try
  {
    /*
    There are a number of ways to instantiate an instance of the class. In this example, we’re using shared pointers. 
    We just need to call createSharedInstance with a reference to the plugin: 
    This can be either the fully-qualified type of the plugin class (the type attribute of the declaration XML file, e.g. polygon_plugins::Square), 
    or the optional magic name (the name attribute of the declaration XML file, e.g., awesome_triangle).    
    */
    std::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createSharedInstance("awesome_triangle");
    triangle->initialize(10.0);

    std::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createSharedInstance("polygon_plugins::Square");
    square->initialize(10.0);

    printf("Triangle area: %.2f\n", triangle->area());
    printf("Square area: %.2f\n", square->area());
  }
  catch(pluginlib::PluginlibException& ex)
  {
    printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
  }

  return 0;
}
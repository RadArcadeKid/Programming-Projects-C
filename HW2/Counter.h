/**
	JAKE HENSON
	Homework 2
	Counter.h - Serves as the declaration AND implementation of the counter T class
  Run using the Makefile along with testcases - type "test" to run
*/
#ifndef _COUNTER_H_
#define _COUNTER_H_
#include <string> //include type string so that we can use it throughout
#include <vector> //because we will need to use a vector to store map data in
#include <map> //include map cause you need it for maps (duh)
#include <iostream> //include iostream operator so you can overload it

template <class T>
class Counter{
public:

  Counter(); //empty constructor

  Counter(std::vector<T> vect); //constructor for a vector

  void Increment(T obj_increment); //increments requested by 1

  void Increment(T obj_increment, const int num_increments); //increments requested by n

  void Decrement(T obj_decrement); //decrements requested by 1

  void Decrement(T obj_increment, const int num_increments); //decrements requested by n

  //helper function
  void BubSort(int unsorted_array[], int size); //(helper function) literally just a bubble sort

  std::vector<T> MostCommon(int num_common); //finds the most number of common objects

  std::vector<T> LeastCommon(int num_common); //finds the least number of common objects

  std::map<T, int> NormalizedWeights(); //accesses all the normalized weights

  std::vector<T> AllKeys();  //accesses all the keys of the T map, returns them as a vector

  std::vector<int> AllValues();  //accesses all the values of the T map, returns them as a vector

  std::map<T, int> get_map(); //return a "regular" map based on the one we have

  int TotalCounts(); //sums the count of all the objects in the map

  int TotalCounts(T min, T max); //sums the count of all the objects in the map bettween the min and the max

  void Remove(T obj_to_remove); //removes this object from the map

  //helper function
  bool AreVectorsEqual(std::vector<T> vec1, std::vector<T> vec2); //(helper function) returns true if vectors are equal


  //== override operator
  // -- This did not end up working how I thought it would...
  //implemented in-line because I had trouble implmenting it outside of the class
  // bool Counter::operator==(const std::map<T, int> &map_test){
  //     for (auto& i : map_){
  //         if(map_.find(i) == map_.end()){
  //           return false;
  //         }
  //         else if(map_.at(i) != map_test.at(i)){
  //           return false;
  //         }
  //     }
  //     return true;
  // }

  //<< override operator
  //implemented in-line because I had trouble implmenting outside of the class
  friend std::ostream &operator<<(std::ostream& output, const Counter &counter_obj){
    output << "map_ : {";
    for(auto& i : counter_obj.map_){
      output << "{ " << i.first << " : " << i.second << " }"; //print the keys and values at each point in the map
    }
    output << "} ";
    return output;
  }

private:
  std::map<T,int> map_; //private map variable where objects will be mapped
};

//////////////////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION  OF THE REST OF THE FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////



/**
  Constructor (empty) - Creates a new empty map and sets it to the private map_
*/
template <class T>
Counter<T>::Counter(){
  std::map<T,int> empty_map;
  map_ = empty_map; //set the map_ equal to this new empty one because we haven't initialized anything yet..
}


/**
  Constructor that maps the map to elements in the vector
  @params - vect - All objects from here will go into the map
*/
template <class T>
Counter<T>::Counter(std::vector<T> vect) {
  for(int i = 0; i < vect.size(); i++){ //initialize all elements from vector into map_
    if(map_.find(vect[i]) == map_.end()){ //if the element is NOT in the map already...
      map_.insert({vect[i], 1});
    }
    else{
      map_.at(vect[i]) += 1; //update count
    }
  }
}

/**
  Increments the object by one, adds the object to the map
  @params - Takes in an object to increment, obj_increment of type T and adds to its count by 1
*/
template <class T>
void Counter<T>::Increment(T obj_increment){
  if(map_.find(obj_increment) == map_.end()){ //if the element is NOT in the map already...
    map_.insert({obj_increment, 1});//insert the object into the map
  }
  else{
    map_.at(obj_increment) += 1; //otherwise, just update count since it's already there
  }
}

/**
  Increments the object by the requested amount, adds the object to the map if it's not already there
  @params - Takes in obj_increment of type T and adds to its count by the num_increments value
*/
template <class T>
void Counter<T>::Increment(T obj_increment, const int num_increment){
  if(map_.find(obj_increment) == map_.end()){ //if the element is NOT in the map already...
    map_.insert({obj_increment, num_increment}); //insert the object into the map
  }
  else{
    map_.at(obj_increment) += num_increment; //update count by the number of increments
  }
}


/**
  Decrements the object by one, removes the object from the map
  @params - Takes in an object to decrement, obj_increment of type T and adds to its count by 1
*/
template <class T>
void Counter<T>::Decrement(T obj_decrement){

  if(map_.find(obj_decrement) != map_.end()){ //if the element is in the map, then decrement
    if(map_.at(obj_decrement) == 1){ //if there is only 1 object
      map_.erase(obj_decrement);//remove this object from the map
    }
    else{ //if there's more than one occurance of this object...
      map_.at(obj_decrement) -= 1;
    }
  }
}

/**
  Decrements the object by the requested amount, adds the object to the map if it's not already there
  @params - Takes in obj_increment of type T and adds to its count by the num_increments value
*/
template <class T>
void Counter<T>::Decrement(T obj_decrement, const int num_decrement){
  if(map_.find(obj_decrement) != map_.end()){ //if the element is in the map, then decrement
    if(num_decrement >= map_.at(obj_decrement)){ //if the amount you want to decrement by exceeds the count
      map_.erase(obj_decrement);//remove this object from the map
    }
    else{ //otherwise it's safe to just decrement
      map_.at(obj_decrement) -= num_decrement;
    }
  }
}


/**
  BubSort - literally just a bubble sort, used for sorting the values in the arrays
  (yeah, I know bubble sorts are horrendously inefficient, but it's what I know how to write. Not going for ultra-speed here...)
  @params - Takes in an array and a size of the array
*/
template <class T>
void Counter<T>::BubSort(int unsorted_arr[], int size)
{
   int i, k;
   bool swapped;
   for (i = 0; i < size-1; i++)
   {
     swapped = false;
     for (k = 0; k < size-i-1; k++)
     {
        if (unsorted_arr[k] > unsorted_arr[k+1])
        {
          //swap these elements!
           int temp_val = unsorted_arr[k];
           unsorted_arr[k] = unsorted_arr[k+1];
           unsorted_arr[k+1] = temp_val;
           swapped = true;
        }
     }
     if (!swapped){  //if we haven't swapped...
       break;
     }

   }
}

/**
  Finds the n most common objects in the vector
  @params - takes in num_common (the number of most common objects you'd like)
  @returns - returns a vector with the corrosponding map all_values
*/
template <class T>
std::vector<T> Counter<T>::MostCommon(int num_common){
  std::vector<T> most_common_objs; //a vector which stores the most common map key + values;
  int map_size = map_.size();
  int all_values[map_size]; //an array of ALL values in the map


  ///just a side note here - there's probably a way better way to do this than the way I've made it here...
  //this was just the only way I could think to properly order the map

  //populate the values for each object into the all_values array...
  int i = 0; //index
  for (auto& x: map_){
      all_values[i] = x.second; //populate the value of this spot in the map into the array for later use
      i++;
  }

  //sort all values (using my bubblesort helper function)
  BubSort(all_values, map_size);

  //populate the n greatest values into the most_common_objs vector
  for(int i = 0; i < num_common; i++){
    most_common_objs.push_back( map_[ all_values[num_common-i] ] ); //find the map at this index, populate it
  }

  return most_common_objs;
}

/**
  Finds the n least common objects in the vector
  @params - takes in num_common (the number of least common objects you'd like)
  @returns - returns a vector with the corrosponding map all_values
*/
template <class T>
std::vector<T> Counter<T>::LeastCommon(int num_common){
  std::vector<T> least_common_objs; //a vector which stores the most common map key + values;
  int map_size = map_.size();
  int all_values[map_size]; //an array of ALL values in the map
  int i = 0; //index for array population

  //populate the values for each object into the all_values array...
  for (auto x: map_){
      all_values[i] = x.second; //populate the value of this spot in the map into the array for later use
      i++;
  }

  //sort all values (using my bubblesort helper function)
  BubSort(all_values, map_size);

  //populate the n greatest values into the most_common_objs vector
  for(int i = 0; i < num_common; i++){
    least_common_objs.pushback( map_[ all_values[i] ] ); //find the map at this index, populate it
  }

  return least_common_objs;
}



/**
  Converts the counter to the 'normalized' weights
  @returns a map with "normalized" weights
*/
template <class T>
std::map<T, int> Counter<T>::NormalizedWeights(){
  std::map<T, float> normalized_map = get_map(); //make a copy of the current map
  int sum = TotalCounts();  //the sum of all objects
  int i = 0;

  //for every element in the normalized map...
  for (auto& x: map_){
    float weight = x.first / sum; //the weight for every point is the value at the key divided by the sum (percentage)
    normalized_map.at(x) = weight; //then just set this normalized_map at that element
  }

  return normalized_map;
}


/**
  Accesses all the keys of the T map, returns them as a vector
  @returns a vector with all of the keys
*/
template <class T>
std::vector<T> Counter<T>::AllKeys(){
  std::vector<T> all_keys; //a vector which stores all map keys
  int i = 0; //for indexing thru the vector

  //populate the values for each object into the all_key vector
  for (auto& x: map_){
      all_keys[i] = x.first; //populate the vector with the key
      i++;
  }
  return all_keys;
}

/**
  Accesses all the values of the T map, returns them as a vector
  @returns a vector with all of the values
*/
template <class T>
std::vector<int> Counter<T>::AllValues(){
  std::vector<int> all_values; //a vector which stores all map values
  int i = 0; //for indexing thru the vector

  //populate the values for each object into the all_key vector
  for (auto& x: map_){
      all_values[i] = x.second; //populate the vector with the key
      i++;
  }
  return all_values;
}

/**
  Returns "regular" map based on the current map
  @returns a map identicial to T
*/
template <class T>
std::map<T, int> Counter<T>::get_map(){
  std::map<T, int> normal_map; //map to return

  normal_map.insert(map_.begin(), map_.end()); //insert all objects into the normal map

  return normal_map; //return the map
}

/**
  Calculates the total count of all the objects in the map
  @returns an integer of total objects in the map
*/
template <class T>
int Counter<T>::TotalCounts(){
  int sum = 0;
  std::vector<int> all_values = AllValues(); //get the vector of all of the values

  for(unsigned int i = 0; i < all_values.size(); i++){ //sum all of these elements together
    sum += all_values[i];
  }

  return sum; //and return the sum of all objects
}

/**
  Calculates the total count of all the objects in the map bettween the min and max values
  @params - passes in T min object and T max, which will determine the range of objects
  @returns an integer of total objects in the map (between the two values)
*/
template <class T>
int Counter<T>::TotalCounts(T min, T max){
  int sum = 0;

  std::vector<T> all_keys = AllKeys(); //store all the keys of map_
  std::vector<int> all_values = AllValues(); //store all the values of map_
  int min_index_val; //the index where the minimum object occurs
  int max_index_val; //the index where the maximum object occurs

  if(all_keys.size() == 0){
    return 0; //just return if it's empty - no need to do all that math
  }

  //iterate through all the keys until we've found WHERE the min and max value are in relation to the map
  for(int i = 0; i < all_keys.size(); i++){
      if(all_keys[i] == min){
        int min_index_val = i;
      }
      if(all_keys[i] == max){
        int max_index_val = i;
      }
  }

  //iterate through all of the objects in the vector within the range from min to max index we found earlier...
  for(int i = min_index_val; i <= max_index_val; i++){
      sum += all_values[i]; //sum the values of all the objects together (since we don't need to map them back onto anything)
  }

  return sum;
}

/**
  Removes the requested object from the map
  @params - takes in an object the user wants to remove
*/
template <class T>
void Counter<T>::Remove(T obj_to_remove){
  map_.erase(obj_to_remove); //literally just remove the object
}


/**
  HELPER FUNCTION
  Compares if the two vectors are equal.
  @params - takes in two vectors to be compared
  @returns an integer of total objects in the map
*/
template <class T>
bool Counter<T>::AreVectorsEqual(std::vector<T> vec1, std::vector<T> vec2){
  if(vec1.size() != vec2.size()){ //obviously if the two vectors are not the same size then they're not ==
    return false;
  }

  for(unsigned int i = 0; i < vec1.size(); i++){
    if(vec1[i] != vec2[i]){ //ake sure every element in the vector matches
      return false;
    }
  }

  //otherwise, they're equal...
  return true;
}



//header guard
#endif //_COUNTER_H

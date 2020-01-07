#ifndef _EARTH_H_
#define _EARTH_H_
//JAKE HENSON
//IN CLASS LECTURE

class Earth {
public:
	//int num_trees_;
	static int num_trees_;

	static Earth& GetInstance() {
		// gets instantiated the first time
		static Earth instance; // guaranteed to be destroyed

		return instance;
	}

    int get_population() { return population_; };

    void IncreasePopulation() { population_ += 1; };

	// Delete the methods we don't want
	Earth(Earth const&) = delete; // copy constructor
	//copy makes another instance of this class, and delete it
	void operator=(Earth const&) = delete; // assignment operator

 private:
 	Earth();  // private constructor

    int population_;

};  // class Earth

#endif  // _EARTH_H_

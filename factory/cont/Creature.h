#ifndef _CREATURE_H_
#define _CREATURE_H_

//JAKE HENSON
//IN CLASS LECTURE
class Creature {
public:
    Creature(int age): age_(age)
    {
        std::vector<Disease *> tmp;
        this->diseases_ = tmp;
    }

    int get_age() const { return age_; };

    void age(int years) { age_ += years; };

    std::vector<Disease *> get_diseases() const {return diseases_; };

    void Spread(Creature * c2);
    void Infect(Disease * d) { diseases_.push_back(d); };

    friend std::ostream& operator<<(std::ostream &os, const Creature &d);

    // 1) Create a virtual Creature * Clone() method.
    // When a creature is cloned, the clone starts at age 0
    // Diseases that are hereditary should be inherited.
    virtual Creature * Clone(){
      //call creatures constructor
      //call other methods to ensure it has the approriate diesases
      Creature * c = new Creature(0);
      for(unsigned int i = 0; i < diseases_.size(); i++){
          if(diseases_.at(i)->get_is_hereditary() == true){
            c->Infect(diseases_.at(i));
          }
      }
      return c;
    }

private:
    int age_;
    std::vector<Disease *> diseases_;
};


// 2) Create 1 subclass of Creature. For this subclass,
// make its cloning behavior slightly different.
// For instance, some Cloned creatures might also inherit non-hereditary diseases.
// It's up to you!
class Alien: public Creature{
public:
  Creature();
private:
}

// 3) In your main.cpp, instantiate your subclass. (the rest of the work for this
// part of the exercise will happen in main.)

#endif // _CREATURE_H_

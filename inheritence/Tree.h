#ifndef _TREE_H_
#define _TREE_H_
//JAKE HENSON
//IN CLASS LECTURE
class Tree {
    public:

        void Seed() { number_seeds_ += 1; };
        //vitual void Seed() { number_seeds_ += 1; };

        int get_number_seeds() { return number_seeds_; }

    private:
        static int number_seeds_;
};

#endif // _TREE_H_


class SubTree : public Tree {
public:
  void Seed(){
    Tree::Seed();
    Tree::Seed();
  }
};

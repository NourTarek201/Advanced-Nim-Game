#include <iostream>
using namespace std;
class maingame{
    protected:
        int coins = 23;
    public:
        int Gmove(int new_coins){
            for(int i=1;i<4;i++)
                if(Bposition(new_coins-i)){ //predicting future situation of second player to know if he will be in bad position 
                    return i; //get good move
                }
            return false; //good move (false) --> i am in bad position 
        }

        bool Bposition(int new_coins){ 
            if(new_coins==1){
                return true; //u lose the game no good move
            }
            return
                Gmove(new_coins)==0; //not bad position return false bec there is good position
        }
        void winning(int turn){
            if(turn)
                cout<<"\nComputer won !!";
            else{
                cout<<"\nHuman won !!";
            }
        }
        virtual void play(){
            int Human=1;
            int comp=0;
            int turn =1;
            cout<<"We have "<<coins<<" coins to start playing with\nYou can subtract 1,2,3 only from total coins\n";
            while(coins>1){
                    if(turn){
                        //v2 func coose p

                        cout<<"\n___Human's turn___\nEnter coins you will take :";
                        int choice;
                        cin>>choice;
                        if(choice < 1 || choice > 3 || choice > coins) { 
                            cout << "\nPls pick 1 to 3 coins and <= remaining coins\n";
                            continue;
                        }
                        //version 1 usage
                        

                        
                        coins-=choice; //maingame
                        cout<<"\nCoins = "<<coins<<endl; //maingame
                        // hcoins+=sub; //v1
                        // variants();
                        

                        turn = comp;
                    }
                    else{
                        int sub=Gmove(coins);
                        if(sub==0)
                            sub=1;
                        cout<<"\n___Computer's turn___\nComputer picks :"<<sub<<endl;
                        
                        
                        //sp 
                        coins-=sub; //all
                        cout<<"\nCoins = "<<coins<<endl; //all

                        //comp_coins+=sub; //v1


                        turn = Human;
                    }
            }
            winning(turn);
        }
};


//last one is taken
//even number must be obtained
class variant1 :public maingame{
    private:
        int comp_coins=0;
        int hcoins=0;
    public:
        virtual void play(){
            int Human=1;
            int comp=0;
            int turn =1;
            cout<<"We have "<<coins<<" coins to start playing with\nYou have to make your pile contain an even number\nsubtract 1,2,3 only from total coins \n";
            while(coins>0){
                    if(turn){
                        cout<<"\n\nHuman's turn : ";
                        int choice;
                        cin>>choice;
                        if(choice < 1 || choice > 3 || choice > coins) { 
                            cout << "\nPls pick 1 to 3 coins and <= remaining coins\n";
                            continue;
                        }
                        coins-=choice; 
                        cout<<"Coins= "<<coins<<endl;
                        hcoins+=choice;
                        cout<<"Human's pile : "<<hcoins;
                        turn = comp;
                    }
                    else{
                        int sub=Gmove(coins);
                        if(sub==0)
                            sub=1;

                        cout<<"\n\nComputer's turn ..Computer picks :"<<sub<<endl;
                        coins-=sub; 
                        cout<<"Coins = "<<coins<<endl; 
                        comp_coins+=sub; 
                        cout<<"Computer's pile = "<<comp_coins;
                        turn = Human;
                    }
            }
            cout<<endl;
            comp_coins%2==0?winning(1):winning(0);
        }
};
class variant2 :public maingame {
    private:
        int p1,p2,p3;
    public:
        void piles(){
            while(true){
                if((coins-3)%3 == 0){
                    p3=coins/3;
                    p2=(coins/3)+1;
                    p1=(coins/3)+2;
                    break;
                }
                else{
                    coins++;
                    continue;
                }
            }
        }
        int sum(){
            return p1+p2+p3;
        }
        virtual void play(){
            int Human=1;
            int comp=0;
            int turn =1;
            cout<<"We have 3 piles of coins to start playing with\nYou can subtract 1,2,3 only from each pile\n";
            piles();
            while(sum()>1){
                    if(turn){
                        //v2 func
                        cout<<"\n___Human's turn___";
                        int which_pile;
                        cout<<"\nPile 1: "<<p1<<"\nPile 2: "<<p2<<"\nPile 3: "<<p3<<endl;
                        cout<<"Pile ? : ";
                        cin>>which_pile;
                        

                        cout<<"Please pick the amount of coins to take: ";
                        int choice;
                        cin>>choice;
                        if(choice < 1 || choice > 3 || choice > coins) { 
                            cout << "\nPls pick 1 to 3 coins and <= remaining coins\n";
                            continue;
                        }

                        //version 2 usage
                        which_pile==1?p1-=choice:which_pile==2?p2-=choice:p3-=choice;
                        turn = comp;
                    }
                    else{
                        cout<<"\n___Computer's turn___";
                        
                        cout<<"\nPile 1: "<<p1<<"\nPile 2: "<<p2<<"\nPile 3: "<<p3<<endl;

                        //picks pile with most amount of coins
                        cout<<"Computer chooses ";
                        pilemove();
                        
                        turn = Human;
                    }
            }
           
            winning(turn);
        }

        int move(int new_coins){
            if(new_coins==1){
                new_coins=2;
            }
            return maingame::Gmove(new_coins);
        }

        //largest pile's coins
        int greatpile(){
            int pile=p1;
            if(pile<p2){
                pile=p2;
            }
            else if(pile<p3){
                pile=p3;
            }
            return pile;
        }

        void pilemove(){
            int pile=greatpile(); //largest pile coins
            int pick=move(pile);
            if(pick ==0 ){
                pick=1;
            }
            if(pile==p2){
                cout<<"pile 2";
                p2-=pick;
            }
            else if(pile==p3){
                cout<<"pile 3 ";
                p3-=pick;
            }
            else{
                cout<<"pile 1";
                p1-=pick;
            }
            
            cout<<"\nComputer picks : "<<pick<<" coins\n";
        }
};




int main(){
    maingame *ptr;
    int ver;
    cout<<"Welcome user ..We have 3 versions of Nim game\nPlease choose which version you want to play now\n1)Main game version\n2)Even pile version\n3)Three piles version\n";
    cin>>ver;
    ver==2?ptr=new variant1():ver==3?ptr=new variant2():ptr=new maingame();
    ptr->play();
}
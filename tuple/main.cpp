#include <iostream>

// дефолт тюпл, не юзаем в обыяных ситуациях
template<typename...TTail>
class TUPLE{};

//тюпл, который будем вызывать рекурсивно
template<typename THead,typename...TTail>

//создаем тюпл на 1 параметр THead value_ и хвост, далее создаем родителя рекурсивно
//передавая хвост, родитель примет THead value_ и новый хвост, на 1 меньше предыдущего
class TUPLE<THead,TTail...>:public TUPLE<TTail...>{
    using TBase = TUPLE<TTail...>;
    
public:
    TUPLE(THead head_,TTail... tail_) : TBase(tail_...), value_(head_){
    }
    
    //Print_Tuple рекурсивынй, вызовется для шаблона, который вызвали и всех его родителей
    void Print_Tuple(){
        std::cout << value_<<std::endl;
        TBase::Print_Tuple();
    }
    
    //set_value не рекурсивный, обращается к конкретному элелменту
    void set_value(THead& val){
        value_=val;
    }
    
    //ну типа просто геттер что бы можно было взять отдельный элемент тюпла
    THead get_value(){
        return value_;
    }
    
private:
//у каждого шаблона доступен всего 1 элемент, первый параметр вызванного конструктора
    THead value_;
};

//для завершения прекрсии явно вызываем шаблон с 0 параметрами
//и методом Print_Tuple, который ничего не сделает
//что бы в main не вызывать пустой принт ставим модификатор
template< >
class TUPLE< >{
protected:
    void Print_Tuple(){}
};

int main() {
    TUPLE<int,double,short,float,std::string,char> Name_Tuple(1,2.1,35,0.43333,std::string("hello"),'H');

    //что бы обратиться к конкретному эллементу тюпла, нужно явно указать шаблон, в котором этот элемент - голова тюпла
    std::string a="15";
    Name_Tuple.TUPLE<std::string, char>::set_value(a);

    Name_Tuple.Print_Tuple();
    
    std::cout << "\n\n";
        
    std::cout<< Name_Tuple.TUPLE<float,std::string, char>::get_value()<< std::endl;
    
    return 0;
}


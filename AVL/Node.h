template <typename T>
class Node
{
public:
    int FE;
    T value;
    Node<T>*m_pSig[2];
public:
    Node(T value){
        this->value=value;
        this->m_pSig[1]=this->m_pSig[0]=0;
        this->FE=0;
    }
};

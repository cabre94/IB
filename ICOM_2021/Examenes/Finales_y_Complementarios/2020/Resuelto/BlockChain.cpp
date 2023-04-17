#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;


using Transaction = int;

struct Block_data {
    static const unsigned N = 32;
    Block_data(unsigned pcrc) : prevCRC(pcrc) {}
    unsigned prevCRC;      // checksum del bloque previo, 0 si es el primer bloque
    Transaction transactions[N] = { 0 }; // transacciones del bloque
};

struct Block {
    Block(unsigned crc) : data(crc), pNext(nullptr) {}
    Block_data data;			// bloque de datos
    Block* pNext;	      // siguiente bloque en la cadena
};

unsigned genCRC(const Block_data* pBlockData);

class BlockChain {
public:
    // Crea una nueva cadena de bloques y la inicializa como vac�a
    BlockChain() : firstBlock(new Block(0)), currBlock(firstBlock), currTransacIdx(0) {
	}

    // destruye una cadena de bloques liberando todos
    // los recursos asociados
    ~BlockChain() {
		Block* pAux = firstBlock->pNext;

		while(pAux) {  // pAux != nullptr
			delete firstBlock;
			firstBlock = pAux;
			pAux = firstBlock->pNext;
		}
		delete firstBlock;
	}

    // Agrega una nueva transacci�n a la cadena
    void addTransaction(Transaction t){
		if(currTransacIdx == currBlock->data.N){ // bloque nuevo
			currBlock->pNext = new Block(genCRC(&currBlock->data));
			currBlock = currBlock->pNext;
			currBlock->data.transactions[0] = t;
			currTransacIdx = 1;
		}else{
			currBlock->data.transactions[currTransacIdx] = t;
			currTransacIdx++;
		}
	}

    // funci�n que devuelve verdadero o falso indicando la validez de la cadena
    bool chainValid() {
		Block* pAux = firstBlock;

		while (pAux->pNext) {
			if(genCRC(&pAux->data) != pAux->pNext->data.prevCRC)
				return false;
			
			pAux = pAux->pNext;
		}
		
		return true;
	}

private:
    Block* firstBlock;		   // primer bloque de la cadena
    Block* currBlock;	       // bloque en generaci�n
    unsigned currTransacIdx;   // �ndice de transacci�n dentro de currBlock
};


static unsigned crc32_for_byte(unsigned int  r) {
    for (int j = 0; j < 8; ++j)
        r = (r & 1 ? 0 : (unsigned )0xEDB88320L) ^ r >> 1;
    return r ^ (unsigned )0xFF000000L;
}

static void crc32(const void* data, size_t n_bytes, unsigned * crc) {
    static unsigned   table[0x100];
    if (!table[0])
        for (size_t i = 0; i < 0x100; ++i)
            table[i] = crc32_for_byte(i);
    for (size_t i = 0; i < n_bytes; ++i)
        *crc = table[(unsigned char)*crc ^ ((unsigned char*)data)[i]] ^ *crc >> 8;
}

unsigned  genCRC(const Block_data* pBlockData) {
    unsigned  crc = 0;
    crc32(pBlockData, sizeof(Block_data), &crc);
    return crc;
}


int main() {
	
    srand((unsigned ) time(NULL));
    BlockChain bc;
    int count = 10000;
    while (count--)
        bc.addTransaction(rand());

    assert(bc.chainValid());

    return 0;

}

// Con amor, Cabre.
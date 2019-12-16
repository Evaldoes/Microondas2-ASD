#ifndef DECODER_H_
#define DECODER_H_

class Decoder {
    private:
           int q;
    public:
           Decoder ();
           void decode (bool b3, bool b7);
           int getQ ();
};

#endif

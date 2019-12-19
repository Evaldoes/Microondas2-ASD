#ifndef DECODER_H_
#define DECODER_H_

class DecoderKBD {
    private:
           int q;
    public:
           DecoderKBD ();
           void decode (bool b3, bool b7);
           int getQ ();
};

#endif

#include "h2/DecoderKBD.h"

DecoderKBD::DecoderKBD(){
         q = 0;
}
void DecoderKBD::decode(bool b3, bool b7){
      if (b3 == 0 && b7 == 0) {
           q = 0;
      }
      else  if (b3 == 1 && b7 == 0) {
           q = 3;
      }
      else  if (b3 == 0 && b7 == 1) {
           q = 7;
      }
      else  if (b3 == 1 && b7 == 1) {
           q = 0;
      }
      else {
           q = 0;
      }
}

int DecoderKBD::getQ(){
	return q;
}

/*
  We know 1/A + 1/B = 1/H 
  Also we know that A*A + L1*L1 = W*W and B*B + L2*L2 = W*W
  A = sqrt(W*W + L1*L1) 
  B = sqrt(W*W + L2*L2)
  And having these Heights A and B the estimated height for the point where they intercept
  is (A*B)/(A + B) if this estimated height is very close to the H we have then this is the answer
        abs(Estimated Height - Height) <= EPS -> Found Answer
        (Estimated Height - Height) > 0 -> Our width is in [mid, hi]
        (Estimated Height - Height) < 0 -> Our width is in [lo, mid]
*/
#define EPS 1e-7
double binarySearch(){
    double A, B, lo, w, hi,assumed_h;
    lo = 0;
    hi =  min(a,b);
    while(1){
        w = (hi-lo)/2+lo;
        A = sqrt(a*a-w*w), B = sqrt(b*b-w*w);
        assumed_h = A*B/(A + B);
        if(fabs(assumed_h-h)<=EPS){
          // width found
          return w;
        }
        if(assumed_h>h)lo=w;
        else hi=w;
    }
    return -1;
}

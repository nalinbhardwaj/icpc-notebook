/**
 * Author: Jingbo Shang/SGTU
 * Date: 2020-02-15
 * Source: SGTU notebook
 * Description: Given a convex hull and a line, finds their intersection
 * Time: O(log(n))
 * Status: 
 */
#pragma once
double calc(point a, point b){
  double k=atan2(b.y-a.y , b.x-a.x); if (k<0) k+=2*pi;return k;
}//= the convex must compare y, then x. a[0] is the lower-right point
//======= three is no 3 points in line. a[] is convex 0~n-1
void prepare(point a[] ,double w[],int &n) {
  int i; rep(i,n) a[i+n]=a[i];
  a[2*n]=a[0];
  rep(i,n) { w[i]=calc(a[i],a[i+1]);w[i+n]=w[i];}
}
int find(double k,int n , double w[]){
  if (k<=w[0] || k>w[n-1]) return 0; int l,r,mid; l=0; r=n-1;
  while (l<=r) { mid=(l+r)/2;if (w[mid]>=k) r=mid-1; else l=mid+1;
  }return r+1;
}
int dic(const point &a, const point &b , int l ,int r , point c[]) {
  int s; if (area(a,b,c[l])<0) s=-1; else s=1; int mid;
  while (l<=r) {
    mid=(l+r)/2; if (area(a,b,c[mid])*s <= 0) r=mid-1;
    else l=mid+1;
  }return r+1;
}
point get(const point &a, const point &b, point s1, point s2) {
  double k1,k2; point tmp; k1=area(a,b,s1); k2=area(a,b,s2);
  if (cmp(k1)==0) return s1; if (cmp(k2)==0) return s2;
  tmp=(s1*k2 - s2*k1) / (k2-k1);
  return tmp;
}
bool line_cross_convex(point a, point b ,point c[] , int n, point &cp1, point
    &cp2 , double w[]) {
  int i,j;
  i=find(calc(a,b),n,w);
  j=find(calc(b,a),n,w);
  double k1,k2;
  k1=area(a,b,c[i]); k2=area(a,b,c[j]);
  if (cmp(k1)*cmp(k2)>0) return false; //no cross
  if (cmp(k1)==0 || cmp(k2)==0) {
    //cross a point or a line in the convex
    if (cmp(k1)==0) {
      if (cmp(area(a,b,c[i+1]))==0) {cp1=c[i]; cp2=c[i+1];}
      else cp1=cp2=c[i];
      return true;
    }
    if (cmp(k2)==0) {
      if (cmp(area(a,b,c[j+1]))==0) {cp1=c[j];cp2=c[j+1];
        }else cp1=cp2=c[j];
    }return true;
  }
  if (i>j) swap(i,j); int x,y;
  x=dic(a,b,i,j,c); y=dic(a,b,j,i+n,c);
  cp1=get(a,b,c[x-1],c[x]); cp2=get(a,b,c[y-1],c[y]);
  return true;}

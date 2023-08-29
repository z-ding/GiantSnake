#include "node.h"
allpurposenode::allpurposenode(char c) {
	text = c;
	prev = nullptr;
	next = nullptr;
}
allpurposenode::allpurposenode(char c, int _x, int _y) {
	text = c;
	x = _x;
	y = _y;
	prev = nullptr;
	next = nullptr;
}
allpurposenode::allpurposenode(char c, int _x, int _y, int _r) {
	text = c;
	x = _x;
	y = _y;
	r = _r;
	prev = nullptr;
	next = nullptr;
}
allpurposenode::~allpurposenode() {

}
snode allpurposenode::getter() {
	return { x,y, r,text,prev,next };
};
void allpurposenode::nodexysetter(float _x, float _y) {
	x = _x;
	y = _y;
}
void allpurposenode::nodetextsetter(char c) {
	text = c;
};
void connectnodes(std::shared_ptr<allpurposenode> n1, std::shared_ptr<allpurposenode> n2) {
	n1->next = n2;
	n2->prev = n1;
};
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "BinaryTree.h"


// 메인 사용부 샘플 코드

void main()
{
	BSearchTree Tree;

	Tree.InsertNode(10);
	Tree.InsertNode(11);
	Tree.InsertNode(12);
	Tree.InsertNode(5);
	Tree.InsertNode(6);

	Tree.PreorderPrint();

	Tree.deleteNode(10);

	Tree.PreorderPrint();
	//printf("10,11,12,5,6 Node Insert\n\n");
	//_getch();
}
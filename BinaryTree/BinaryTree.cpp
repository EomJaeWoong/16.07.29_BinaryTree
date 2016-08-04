#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

BSearchTree::BSearchTree()
{
	m_pRoot = NULL;
	m_iNodeCount = 0;
}

BSearchTree::~BSearchTree()
{
	ReleaseTree();
}

//------------------------------------------------------
// 새로운 데이터를 추가한다.
//------------------------------------------------------
bool BSearchTree::InsertNode(int iData)
{
	st_TNODE *pNode = new st_TNODE;
	CreateNode(pNode, iData);

	if (m_pRoot == NULL)
	{
		m_pRoot = pNode;
		return true;
	}

	return linkNode(m_pRoot, pNode);
}


//------------------------------------------------------
// 트리의 데이터를 삭제한다.
//------------------------------------------------------
void BSearchTree::deleteNode(int iData)
{
	unlinkNode(m_pRoot, NULL, iData);
}

//------------------------------------------------------
// 트리 전체 삭제
//------------------------------------------------------
bool BSearchTree::ReleaseTree(void)
{
	releaseNode(m_pRoot);

	return true;
}

//------------------------------------------------------
// 전위순회 방식 출력
//------------------------------------------------------
void BSearchTree::PreorderPrint(st_TNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_pRoot;
	if (pNode == NULL)	return;

	for (int iCnt = 0; iCnt < iDepth; iCnt++)
		printf(" ");

	if (iLR == 0)			printf("[ROOT] ");
	if (iLR == LEFT)		printf("[LEFT %d] ", iDepth);
	if (iLR == RIGHT)		printf("[RIGHT %d] ", iDepth);

	printf("%d", pNode->iData);
	printf("\n");

	PreorderPrint(pNode->pLeft, iDepth + 1, LEFT);
	PreorderPrint(pNode->pRight, iDepth + 1, RIGHT);
}

//------------------------------------------------------
// 중위순회 방식 출력
//------------------------------------------------------
void BSearchTree::InorderPrint(st_TNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_pRoot;
	if (pNode == NULL)	return;

	InorderPrint(pNode->pLeft, iDepth + 1, LEFT);

	for (int iCnt = 0; iCnt < iDepth; iCnt++)
		printf(" ");

	if (iLR == 0)			printf("[ROOT] ");
	if (iLR == LEFT)		printf("[LEFT %d] ", iDepth);
	if (iLR == RIGHT)		printf("[RIGHT %d] ", iDepth);

	printf("%d", pNode->iData);
	printf("\n");

	InorderPrint(pNode->pRight, iDepth + 1, RIGHT);
}

//------------------------------------------------------
// 후위순회 방식 출력
//------------------------------------------------------
void BSearchTree::PostorderPrint(st_TNODE *pNode, int iDepth, int iLR)
{
	if (iDepth == 0)	pNode = m_pRoot;
	if (pNode == NULL)	return;

	PostorderPrint(pNode->pLeft, iDepth + 1, LEFT);
	PostorderPrint(pNode->pRight, iDepth + 1, RIGHT);

	for (int iCnt = 0; iCnt < iDepth; iCnt++)
		printf(" ");

	if (iLR == 0)			printf("[ROOT] ");
	if (iLR == LEFT)		printf("[LEFT %d] ", iDepth);
	if (iLR == RIGHT)		printf("[RIGHT %d] ", iDepth);

	printf("%d", pNode->iData);
	printf("\n");
}


//------------------------------------------------------
// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
//------------------------------------------------------
bool BSearchTree::linkNode(st_TNODE *pParent, st_TNODE *pChild)
{
	if (pParent->iData > pChild->iData)
	{
		if (pParent->pLeft == NULL)
		{
			pParent->pLeft = pChild;
			return true;
		}

		else
			linkNode(pParent->pLeft, pChild);
	}

	else if (pParent->iData < pChild->iData)
	{
		if (pParent->pRight == NULL)
		{
			pParent->pRight = pChild;
			return true;
		}

		else
			linkNode(pParent->pRight, pChild);
	}

	return false;
}


//------------------------------------------------------
// releaseNode 내부에서 호출되는 노드삭제용 재귀함수
//------------------------------------------------------
void BSearchTree::releaseNode(st_TNODE *pNode)
{
	if (pNode == NULL)	return;

	releaseNode(pNode->pLeft);
	releaseNode(pNode->pRight);

	delete pNode;
	pNode = NULL;
}

//------------------------------------------------------
// deleteNode 내부에서 호출되는 위치 찾아 삭제 재귀 함수
//------------------------------------------------------
bool BSearchTree::unlinkNode(st_TNODE *pNODE, st_TNODE *pParent, int iData)
{
	if (pNODE == NULL)	return true;

	//------------------------------------------------------
	// 데이터 탐색
	//------------------------------------------------------
	if (pNODE->iData > iData)
		unlinkNode(pNODE->pLeft, pNODE, iData);
	else if (pNODE->iData < iData)
		unlinkNode(pNODE->pRight, pNODE, iData);

	//------------------------------------------------------
	// 자식노드 없음
	//------------------------------------------------------
	if (pNODE->pLeft == NULL && pNODE->pRight == NULL)
	{
		if (pParent->pLeft == pNODE)
			pParent->pLeft = NULL;
		else if (pParent->pRight == pNODE)
			pParent->pRight = NULL;

		delete pNODE;
		return true;
	}

	//------------------------------------------------------
	// 자식노드가 하나
	//------------------------------------------------------
	if (pNODE->pLeft != NULL && pNODE->pRight == NULL)
	{
		if (pParent->pLeft == pNODE)
		{
			pParent->pLeft = pNODE->pLeft;
			delete pNODE;
		}
		else if(pParent->pRight == pNODE)
		{
			pParent->pRight = pNODE->pLeft;
			delete pNODE;
		}
	}

	else if (pNODE->pLeft == NULL && pNODE->pRight != NULL)
	{
		if (pParent->pLeft == pNODE)
		{
			pParent->pLeft = pNODE->pRight;
			delete pNODE;
		}
		else if (pParent->pRight == pNODE)
		{
			pParent->pRight = pNODE->pRight;
			delete pNODE;
		}
	}

	//------------------------------------------------------
	// 자식노드가 둘
	//------------------------------------------------------
	//else if (pNODE->pLeft == NULL && pNODE->pRight != NULL)
}


//------------------------------------------------------
// 노드 생성
//------------------------------------------------------
void BSearchTree::CreateNode(st_TNODE *pNode, int iData)
{
	pNode -> iData  =	iData;
	pNode -> pLeft  =	NULL;
	pNode -> pRight =	NULL;
}

st_TNODE *BSearchTree::GetRoot()
{
	return m_pRoot;
}
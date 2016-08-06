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
	st_TNODE *pNode = m_pRoot;
	st_TNODE *pParent = NULL, *pTargetNode = NULL;

	//------------------------------------------------------
	// 데이터 탐색
	//------------------------------------------------------
	while (pNode->iData != iData && pNode != NULL)
	{
		pParent = pNode;

		if (pNode->iData > iData)		pNode = pNode->pLeft;
		else							pNode = pNode->pRight;
	}

	//------------------------------------------------------
	// 자식노드 없는 경우
	//------------------------------------------------------
	if (pNode->pLeft == NULL && pNode->pRight == NULL)
	{
		if (pNode == pParent->pLeft)
			pParent->pLeft = NULL;
		else
			pParent->pRight = NULL;

		delete pNode;
	}

	//------------------------------------------------------
	// 자식노드가 하나인 경우
	//------------------------------------------------------
	else if (pNode->pLeft != NULL && pNode->pRight == NULL)
	{
		if (pNode == pParent->pLeft)
			pParent->pLeft = pNode->pLeft;
		else
			pParent->pRight = pNode->pLeft;
		delete pNode;
	}

	else if (pNode->pLeft == NULL && pNode->pRight != NULL)
	{
		if (pNode == pParent->pLeft)
			pParent->pLeft = pNode->pRight;
		else
			pParent->pRight = pNode->pRight;
		delete pNode;
	}

	//------------------------------------------------------
	// 자식노드가 두개인 경우
	//------------------------------------------------------
	else
	{
		//------------------------------------------------------
		// 삭제한 자리에 넣을놈 찾기
		//  ->작은애중 가장 큰놈(L->R)       이걸로 만들기
		//  ->큰애중 가장 작은놈(R->L)
		// 찾은 데이터를 삭제할 위치에 대입시키고
		// 찾은 위치를 실제로 삭제함
		//------------------------------------------------------

		pTargetNode = unlinkNode(pNode->pLeft, pNode);
		pNode->iData = pTargetNode->iData;
		delete pTargetNode;
		//TargetNode -> NULL
	}
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
st_TNODE *BSearchTree::unlinkNode(st_TNODE *pNode, st_TNODE *pParent)
{
	if (pNode->pRight == NULL)		return pNode;

	unlinkNode(pNode->pRight, pNode);
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
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
// ���ο� �����͸� �߰��Ѵ�.
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
// Ʈ���� �����͸� �����Ѵ�.
//------------------------------------------------------
void BSearchTree::deleteNode(int iData)
{
	st_TNODE *pNode = m_pRoot;
	st_TNODE *pParent = NULL, *pTargetNode = NULL;

	//------------------------------------------------------
	// ������ Ž��
	//------------------------------------------------------
	while (pNode->iData != iData && pNode != NULL)
	{
		pParent = pNode;

		if (pNode->iData > iData)		pNode = pNode->pLeft;
		else							pNode = pNode->pRight;
	}

	//------------------------------------------------------
	// �ڽĳ�� ���� ���
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
	// �ڽĳ�尡 �ϳ��� ���
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
	// �ڽĳ�尡 �ΰ��� ���
	//------------------------------------------------------
	else
	{
		//------------------------------------------------------
		// ������ �ڸ��� ������ ã��
		//  ->�������� ���� ū��(L->R)       �̰ɷ� �����
		//  ->ū���� ���� ������(R->L)
		// ã�� �����͸� ������ ��ġ�� ���Խ�Ű��
		// ã�� ��ġ�� ������ ������
		//------------------------------------------------------

		pTargetNode = unlinkNode(pNode->pLeft, pNode);
		pNode->iData = pTargetNode->iData;
		delete pTargetNode;
		//TargetNode -> NULL
	}
}

//------------------------------------------------------
// Ʈ�� ��ü ����
//------------------------------------------------------
bool BSearchTree::ReleaseTree(void)
{
	releaseNode(m_pRoot);

	return true;
}

//------------------------------------------------------
// ������ȸ ��� ���
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
// ������ȸ ��� ���
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
// ������ȸ ��� ���
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
// InsertNode ���ο��� ȣ��Ǵ� ��ġ ã�� �߰� ��� �Լ�
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
// releaseNode ���ο��� ȣ��Ǵ� �������� ����Լ�
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
// deleteNode ���ο��� ȣ��Ǵ� ��ġ ã�� ���� ��� �Լ�
//------------------------------------------------------
st_TNODE *BSearchTree::unlinkNode(st_TNODE *pNode, st_TNODE *pParent)
{
	if (pNode->pRight == NULL)		return pNode;

	unlinkNode(pNode->pRight, pNode);
}


//------------------------------------------------------
// ��� ����
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
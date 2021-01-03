def findDuplicate(arr):
    liDuplicate=[]
    hashIndex=[0]*len(arr)
    for i in arr:
        if hashIndex[i]==0:
            hashIndex[i]=1
        elif hashIndex[i]==1:
            liDuplicate.append(i)

    return liDuplicate

arr=[4, 5, 2, 1, 4, 6, 6]
print(findDuplicate(arr))
// 1.  **Initialization:** Each node creates a routing table with initial distances to neighbors (direct link cost or infinity if no link; zero to itself) and sets the next hop.[1]
// 2.  **Sharing:** Nodes periodically send their routing tables (distance vectors) to direct neighbors[1].
// 3.  **Update:** Upon receiving a neighbor's routing table, a node calculates potential new distances to destinations via that neighbor[1]. If a shorter distance is found, it updates 
// its routing table with the new distance and sets the next hop to the neighbor[1].
// 4.  **Iteration:** Steps 2 and 3 repeat until routing tables converge[7].
// 5.  **Convergence:** The algorithm converges when no routing table changes occur after information exchange, indicating optimal routes are established[2].


#include <stdio.h>

struct node{
    int dist[20];
    int from[20];
}rTable[20];

void main(){
    int costMat[20][20], nodes, count;

    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the cost matrix:\n"); 
    for(int i=0; i<nodes; i++){
        for(int j=0; j<nodes; j++){
            scanf("%d", &costMat[i][j]);
            if (costMat[i][j] == -1) { 
                costMat[i][j] = 1000; 
            }
            
        }
    }

    //Initialize routing table
    for(int i=0; i<nodes; i++){
        for(int j=0; j<nodes; j++){
            rTable[i].dist[j] = costMat[i][j];
            rTable[i].from[j] = j;
        }
        rTable[i].dist[i] = 0; 
        rTable[i].from[i] = i; 
    }


    do{
        count=0;
        for(int i =0; i<nodes; i++){
            for(int j=0; j<nodes; j++){
                for(int k=0; k<nodes; k++){
                    if(rTable[i].dist[j]>rTable[i].dist[k]+rTable[k].dist[j]){
                        rTable[i].dist[j]=rTable[i].dist[k]+rTable[k].dist[j];
                        rTable[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    }while(count!=0);

    // Print the final routing tables
    for(int i=0;i<nodes;i++)
    {
        printf("\n\nRouting table for node %d:\n",i+1);
        printf("Destination\tNext Hop\tDistance\n");
        for(int j=0;j<nodes;j++)
        {
             printf("%d\t\t%d\t\t%d\n",j+1,rTable[i].from[j]+1,rTable[i].dist[j]);
            //printf("\t\nnode %d via %d Distance %d ",j+1,rTable[i].from[j]+1,rTable[i].dist[j]);

        }
    } 
    printf("\n\n");
}





//output
Enter the number of nodes: 3
Enter the cost matrix:
0 2 7
2 0 1
7 1 0


Routing table for node 1:
Destination     Next Hop        Distance
1               1               0
2               2               2
3               2               3


Routing table for node 2:
Destination     Next Hop        Distance
1               1               2
2               2               0
3               3               1


Routing table for node 3:
Destination     Next Hop        Distance
1               2               3
2               2               1
3               3               0

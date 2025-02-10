#include <stdio.h>
#include <stdlib.h>

struct Frame
{ 
    int data;   
    int seqNum; 
};

int ackNum; 
int timeCounter = 5; 
int disconnectFlag = 0; 
struct Frame packet; 
char currentTurn = 's'; 
int hasErrorInFrame = 1; 
int hasErrorInAck = 1;  

void sender();
void receiver();

int main()
{   
    packet.data = 0; 
    packet.seqNum = 0; 
    while (!disconnectFlag)
    {   
        sender(); 
        for(int k = 1; k <= 10000000; k++); 
        receiver(); 
    }
    return 0; 
}

void sender()
{   
    static int ackReceived = 0; 
    if (currentTurn == 's') 
    {  
        if (hasErrorInAck == 0) 
        {   
            printf("SENDER: Sent packet with seq NO: %d\n", packet.seqNum);
            hasErrorInFrame = rand() % 4; 
            printf("%s\n", (hasErrorInFrame == 0 ? "Error While sending Packet" : ""));
            currentTurn = 'r'; 
        }
        else
        {  
            if (ackReceived == 1) 
                printf("SENDER: Received ACK for packet %d\n", ackNum);
            if (packet.seqNum == 5) 
            {  
                disconnectFlag = 1; 
                return;
            }
            packet.data += 1; 
            packet.seqNum += 1; 
            printf("SENDER: Sent packet with seq NO: %d\n", packet.seqNum);
            hasErrorInFrame = rand() % 4; 
            printf("%s\n", (hasErrorInFrame == 0 ? "Error While sending Packet" : ""));
            currentTurn = 'r'; 
            ackReceived = 1; 
        } 
    }
    else
    {   
        timeCounter--; 
        printf("SENDER: Time reducing\n");
        if (timeCounter == 0)
        {
            currentTurn = 's'; 
            hasErrorInAck = 0; 
            timeCounter = 5; 
        }
    }
}

void receiver()
{   
    static int expectedSeqNum = 1; 
    if (currentTurn == 'r') 
    {
        if (hasErrorInFrame != 0)
        { 
            if (packet.seqNum == expectedSeqNum) 
            {   
                printf("RECEIVER: Received packet with seq %d\n", packet.seqNum);
                ackNum = packet.seqNum; 
                expectedSeqNum++; 
                currentTurn = 's'; 
                hasErrorInAck = rand() % 4; 
                printf("%s\n", (hasErrorInAck == 0 ? "Error While sending ACK" : ""));
            }
            else
            {
                printf("RECEIVER: Duplicated packet with seq %d\n", expectedSeqNum - 1);
                ackNum = expectedSeqNum - 1; 
                currentTurn = 's'; 
                hasErrorInAck = rand() % 4; 
                printf("%s\n", (hasErrorInAck == 0 ? "Error While sending ACK" : ""));
            }
        }
    }
}

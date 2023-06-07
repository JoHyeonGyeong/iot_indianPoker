# IoT 프로그래밍 4조


# **인디언 포커 게임(Indian Poker GAME)**


## **1. 프로젝트 계획**

H-Smart4412 타겟 시스템을 이용한 기존 프로젝트 중 중복되지 않는 주제를 찾아보았고, <br> 
그 중 카드 게임인 인디언 포커 게임을 타겟시스템을 이용해 제작하기로 결정

---


## **2. 알고리즘**

![img_01](/Images/Algorithm.jpg)


---

## **3. 게임 규칙 및 순서**

기존 게임과 룰은 동일하지만 플레이어 vs 플레이어가 아닌 컴퓨터 vs 플레이어의 방식으로 변경
따라서 베팅을 하지 않고 플레이어가 크거나 작거나 같다를 베팅해 맞추는 방식이며, A~K카드를 사용하고 플레이어나 컴퓨터 둘 중 7승을 하면 게임 종료
게임 힌트는 지금까지 플레이어가 사용한 카드나, 사용하지 않은 카드를 1번씩 볼 수 있게 해준다.

1. 컴퓨터와 플레이어는 카드 중 각각 하나의 카드(랜덤수)를 부여받는다.
2. 컴퓨터의 수를 플레이어에게 보여주고 컴퓨터는 플레이어의 수가 컴퓨터의 수보다 큰지, 작은지, 같은지에 대한 질문을 한다.
3. 플레이어는 제한 시간 내에 질문에 대한 대답(크다, 작다, 같다)을 하여 대답이 맞으면 승, 틀리면 패한다. 제한 시간 내에 대답을 못할 시 자동 패배.
4. 컴퓨터는 승패 결과를 플레이어에게 알려주고 플레이어의 카드를 보여준다. 이때 사용된 카드는 없어지고 남은 카드를 바탕으로 다시 게임이 반복된다.
5. 13판 중 플레이어가 7선승을 하면 게임을 이기고 7선패를 하면 게임을 지면서 게임이 종료된다. 게임 종료 후 최종 결과를 보여준다.

---

## **4. 게임 코드**

 - **Codes** 디렉토리에 `'IndianPoker.c'`에 작성해놨습니다.
 - 코드 확인 : ['IndianPoker.c'](https://github.com/JoHyeonGyeong/iot_indianPoker/tree/main/Codes/IndianPoker.c)
 - H-Smart4412 타겟 시스템의 장치 테스트 코드 : ['TestCodes'](https://github.com/JoHyeonGyeong/iot_indianPoker/tree/main/Codes/TestCodes)
 
---

## **5. 게임 플레이 영상 (추가 예정)**
플레이 영상 : (유튜브 링크)

- **요약**
1. 게임 인트로
2. 라운드 시작
3. 베팅
4. 베팅 종료 및 결과
5. 게임 종료

---

## **6. 진행 과정**
 - [프로젝트 계획 발표](https://github.com/JoHyeonGyeong/iot_indianPoker/blob/main/Docs/Indian%20Poker_01_20230510.pdf)
 - [프로젝트 중간 발표 1](https://github.com/JoHyeonGyeong/iot_indianPoker/blob/main/Docs/Indian%20Poker_02_20230518.pdf)
 - [프로젝트 중간 발표 2](https://github.com/JoHyeonGyeong/iot_indianPoker/blob/main/Docs/Indian%20Poker_03_20230525.pdf)
 - [프로젝트 중간 발표 3](https://github.com/JoHyeonGyeong/iot_indianPoker/blob/main/Docs/Indian%20Poker_04_20230601.pdf)
 - 프로젝트 최종 발표 : 23. 06. 15 예정

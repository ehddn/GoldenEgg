# GoldenEgg
 겜소디2 수업 3학년 1학기
 
 
 
 
 
 게임 골든에그 v.1.5


<개인적으로 추가한 기능>
머핀을 NPC에게 받을 수 있음
E입력시, 머핀을 먹으면 캐릭터의 체력을 회복함
머핀이 인벤토리에 없다면, 머핀이 없다고 알려줌

총을 쏘는 적에게 총 컴포넌트를 달아줌
(RightHandSocket->Gun)


05.28
주문 시전 기능 추가
불 주문 추가
적에게 시전시 뒤로 밀리면서 피해를 입음



5.30
달리기 맵 추가
마우스로 클릭이 아닌, Q입력시 주문 시전
클리어시 골든에그 맵으로 이동
초반 카운터를 Delay()함수로 초를 샜는데, 굉장히 비효율적임... 다른 타이머 함수 공부중

<과제를 하며 안됬던 점들>
칼 공격모션이 안되는 경우
-> AttackRangeRadius값이 너무 작아 캐릭터를 인식하지 못했었음. 값을 크게 하면 됨

칼 공격모션이 들어온 후 캐릭터에게 휘두르면 언리얼이 팅기는 현상
-> 도저히 모르겠음. 그래서 MeeleeSword의 prox함수를 삭제하고 블루프린트의 onactorbeginoverlap사용함. 문제없이 잘 됨

총알이 발사가 되도, 앞으로 나아가지 않는 경우
-> AddImpulse가 버그가 많은 함수같음. 그냥 블루프린트 편집기의 ProjectileComponent사용하여 스폰될시 무조건 앞으로 나아가도록 함. 문제없이 잘 됨




<필기>



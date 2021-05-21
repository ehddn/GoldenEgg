# GoldenEgg
 겜소디2 수업 3학년 1학기
 
 
 게임 골든에그 v.1.5


칼 공격모션이 안되는 경우
-> AttackRangeRadius값이 너무 작아 캐릭터를 인식하지 못했었음. 값을 크게 하면 됨

칼 공격모션이 들어온 후 캐릭터에게 휘두르면 언리얼이 팅기는 현상
-> 도저히 모르겠음. 그래서 MeeleeSword의 prox함수를 삭제하고 블루프린트의 onactorbeginoverlap사용함. 문제없이 잘 됨

총알이 발사가 되도, 앞으로 나아가지 않는 경우
-> AddImpulse가 버그가 많은 함수같음. 그냥 블루프린트 편집기의 ProjectileComponent사용하여 스폰될시 무조건 앞으로 나아가도록 함. 문제없이 잘 됨



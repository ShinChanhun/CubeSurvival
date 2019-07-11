
//모델들만 모아주는 cpp만 따로 만들어주자-> UCharacterObject 캐릭터 모델들만 모아놓음
//이 클래스를 Pawn으로 만든이유 attack 함수 defense함수 등 여러가지 
#include "APlayerCharacter.h"




// Sets default values 플레이어 캐릭터 디폴드값 설정
AAPlayerCharacter::AAPlayerCharacter()
{
	
	PrimaryActorTick.bCanEverTick = true;
	SetHP(100);
}

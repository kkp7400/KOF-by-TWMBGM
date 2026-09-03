# KOF-by-TWMBGM (WinApi-KOF)

WinAPI(GDI) 기반 King of Fighters 스타일 2D 격투 게임 클론. 팀 3인이 캐릭터별로 클래스를 분담해 만든 2주짜리 학원 팀 프로젝트입니다.

`2021 · C++ / WinAPI(GDI) · 3인 팀 프로젝트 · 2021-04-01 ~ 04-15(2주)`

> "TWMBGM"은 팀 내부 용어로 "세계 제일 미녀 마이"를 의미합니다(공지사항(필독!).txt 실측). 저장소는 팀 작업 스냅샷이며 배포·데모는 없습니다. GitHub Contributors API에는 계정이 연동된 kkp7400 1인만 표시되지만, 저장소 내 `공지사항(필독!).txt`에 3인 팀 구성과 브랜치 워크플로가 문서로 남아 있습니다.

## 데모

![demo](docs/demo.gif)

- `docs/screenshot-title.png` — 타이틀/캐릭터 선택 화면
- `docs/screenshot-mai-attack.png` — 마이 공격 모션
- `docs/screenshot-battle.png` — 대전 화면

## 담당 범위

3인 팀 프로젝트(배현성 본인·팀원 2명)이며, 본인은 캐릭터 "마이(Mai)" 담당으로 클래스 단위 분업을 했습니다. 저장소 내 작업 로그(`공지사항(필독!).txt`, 210403_배현성)에 기재된 본인 작업 내역:

- 마이 좌우 이동
- 마이 공격 4가지 구현
- 마이 커맨드 기술 1개 구현
- 마이 스프라이트 제작

`Mai.cpp`(471줄)에 case/Attack/Command 관련 키워드가 81회 등장하는 상태 분기형 캐릭터 로직입니다. 다른 캐릭터(Iori/Ogong/Tank)는 팀원 2명이 각자의 브랜치에서 담당했습니다.

## 핵심 구현

### `Mai.cpp` — 공격 4종 처리

키 입력에 따라 4가지 공격 상태(Foot_Strong/Foot_Weak/Fist_Strong/Fist_Weak_Attack)로 전환합니다.

```cpp
void Mai::Attack()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown('S') && canState == TRUE)
    {
        frame = 0;
        state = Foot_Strong_Attack;
        UpdateHitCol();
        UpdateAtkCol();
        maxFrame = 11;
        canState = FALSE;
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown('A') && canState == TRUE)
    {
        frame = 0;
        state = Foot_Weak_Attack;
        UpdateHitCol();
        UpdateAtkCol();
        maxFrame = 14;
        canState = FALSE;
    }
```

### `Mai.cpp` — 커맨드기 1개(입력 순서 판정)

정해진 순서로 키(B → M → B)가 들어와야 `command` 배열이 채워지고, 순서를 벗어나면 리셋됩니다.

```cpp
if (KeyManager::GetSingleton()->IsOnceKeyUp('B') && canState == TRUE)
{
    state = Idle;
    UpdateHitCol();
    maxFrame = 16;
    canState = TRUE;
    countCommand++;
    cinCommand = 'B';

    if (countCommand != 1 && countCommand != 3)
    {
        ResetCommand();
    }
    else
    {
        if (countCommand == 1) { command[countCommand - 1] = 'B'; commandTime = 0; }
        if (countCommand == 3) { command[countCommand - 1] = 'B'; commandTime = 0; }
    }
}
```

## 구조

| 경로 | 역할 |
|---|---|
| `KOF by TWMBGM/210317_WinAPI/Mai.*` | 본인 담당 캐릭터(이동/공격 4종/커맨드기) |
| `KOF by TWMBGM/210317_WinAPI/Iori.*`, `Ogong.*`, `Tank.*` | 팀원 담당 캐릭터 |
| `KOF by TWMBGM/210317_WinAPI/Singleton.h`, `KeyManager.*`, `Image.*` | 2D_WinApi와 유사한 매니저/씬 골격 재사용 |
| `KOF by TWMBGM/210317_WinAPI/MainGame.*`, `KofCommonFunc.*` | 게임 루프·공용 함수 |
| `공지사항(필독!).txt` | 팀 작업 규칙(브랜치 워크플로 8개 조항) + 작업 로그 |
| `KOF by TWMBGM.sln` | Visual Studio 솔루션 |

### 팀 작업 규칙 (공지사항(필독!).txt 요약)

개인 브랜치에서 작업 후 자신의 브랜치에 main을 먼저 병합해보고, 정상 동작 확인 후에만 main에 푸시. `.vs`/`x64` 빌드 산출물 폴더는 커밋 제외. 푸시할 때마다 해당 문서에 작업 내용을 기록. 공유 클래스의 멤버 변수·함수를 변경하면 팀에 공지하도록 규칙화되어 있었습니다.

## 실행 방법

- Visual Studio, 솔루션 파일: `KOF by TWMBGM/KOF by TWMBGM.sln`
- 프로젝트: `210317_WinAPI` (WinAPI/GDI, 외부 엔진 의존 없음)
- 스프라이트 리소스는 `Image/Mai/` 등 캐릭터별 폴더에 포함되어 있어 클론 후 바로 빌드 가능합니다.

## 배운 점 / 지금이라면 다르게 할 것

- 커맨드기 판정이 `countCommand` 정수 하나로 입력 순서를 추적하는 방식이라 공격 종류가 늘어나면 분기가 기하급수적으로 늘어납니다. 지금이라면 입력 버퍼 + 커맨드 테이블 매칭 방식으로 바꾸겠습니다.
- 캐릭터 상태가 `switch-case`로만 나뉘어 있어 상태별 로직(입력/애니메이션/충돌)이 한 함수에 섞여 있습니다. FSM 클래스 분리가 필요했습니다.
- Git 브랜치 규칙은 문서로 잘 정리했지만, 공유 클래스(Singleton/KeyManager)를 여러 명이 동시에 수정하면서 발생하는 충돌은 사전에 인터페이스를 더 좁게 설계했어야 줄일 수 있었습니다.

---

## English summary

A 2-week, 3-person school team project (Apr 2021) cloning the visual style/mechanics of King of Fighters on raw WinAPI/GDI. I was solely responsible for the character "Mai": left/right movement, 4 attack moves, 1 command-input special move, and her sprite art (`Mai.cpp`, 471 lines, verified via the team's own work-log document `공지사항(필독!).txt`). GitHub's Contributors API only shows my account because my two teammates' commits weren't linked to GitHub accounts, but the team's branch-workflow rules and per-push work log are preserved in that file (names omitted here — referred to as "2 teammates"). Build via `KOF by TWMBGM/KOF by TWMBGM.sln` in Visual Studio.

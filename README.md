# 개요
linux bash shell 일부 기능과 동일하게 작동하는 shell 구현 프로젝트
<br>
<br>

# 구현 사항
- 파이프 (`|`)
- 리디렉션 (`>`, `>>`, `<`)
- 시그널 (`^c`, `^\`)
- Eof(`^d`)
- 명령어
    - `echo`
    - `cd`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`
- 이스케이프 문자 (`\`)
- history
<br>
<br>

# 실행방법
터미널에 아래 순서대로 명령어를 입력하세요
- `git clone https://github.com/banban555/seshin_shell.git`
- make
- ./minishell
<br>

####readline이 설치되지 않은 경우
- `brew install readline` 입력하여 readline을 설치해야 함
<br>

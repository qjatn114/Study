#if 0
CPU 가 프로그램을 실행하다보면
메모리 공간에 접근해야 하는 경우가 생긴다.
이때 메모리에 접근하고 데이터를 끌어당겨 캐시에 저장한다.
Locality 라고 하는 지역성에 근거하여
데이터가 순차적으로 배치되어 있거나
캐시 사이즈 내에 존재한다면
다시 메모리에 접근할 필요 없이
캐시에서 데이터를 가져와 사용할 수 있다.
그렇지 않다면 다시 메모리에 접근해야 한다.
메모리 계층구조를 생각해보면
메모리의 속도가 느리기 때문에
최대한 캐시를 활용할 수 있도록 프로그래밍 해주는 것이 좋다.
이렇게 프로그래밍 한 것을 캐시 친화성이 높은 프로그램이라고 한다.
#endif
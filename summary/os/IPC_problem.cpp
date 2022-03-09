//生产者消费者模型
//缓冲区是临界资源，需要互斥
//缓冲区满了之后，生产者不能再生产，缓冲区空了之后，消费者不能再使用。需要同步
mutex = 1;
empty = N;
full = 0;
void producer() {
	P(empty);
	P(mutex);
	produce();
	V(mutex);
	V(full);
}
void consumer() {
	P(full);
	P(mutex);//临界区上锁
	consume();
	V(mutex);
	V(empty);
}
void P(S) {
	S--;
	if (S < 0)
		block();
}
void V(S) {
	S++;
	if (S <= 0)
		wakeUp();
}
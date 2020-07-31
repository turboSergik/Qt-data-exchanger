# Qt-data-exchanger


Task3.


В кратце о 3 задаче. Нужно было реализовать источник и приемник данных и научиться передавать данные с как можно большей скоростью. 

Основной задачей я себе поставил уметь получать данные со скоростью 100 number per ms (100k per sec). Но тут я сталкнулся с рядом сложностей.

1. Нужно принимать в разном потоке, класть их в какой-нибудь быстрый контейнер, а с другого потока забирать. Нужно синхронизировать данные в потоках. А это очень и очень медленно.
2. Получить-то данные мы получили, а как их рендерить? Что взять за основную единицу измерения в таймлайне? Миллисекунды? В 1 мс прилетает около 100 одномерных данных. Этого мало. Наносекунды? А вот это уже проблема. 1) Данные не стабильны, нет константного кол-ва данных в мс. 2) Не смог нагуглить адекватный метод измерения времени в Наносекундах в плюсах, да и то с прогрешностью большой будет.
3. После синхронизации через std::mutex скорость обмена данными, следовательно и рендера упала примерно в 100~150 раз. Мьютекс ацтой. Нужно ускорять.
4. Сделал ускорение через очередь запросов.Теперь каждая единица данных не лочит мьютекс, только когда их достаточно собралось. Хорошо, немного ускорили. Но всё равно этого недостаточно. 

Поэтому я всё таки остановился на 1к per sec, вместо 100k. Сколько не пытался, какая либо из 1-3 проблем давала о себе знать

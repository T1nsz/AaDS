//Вариант 20.
//Некоторая железнодорожная компания обслуживает n станций S1,...,Sn.
//Она предполагает улучшить информационное обслуживание клиентов, установив терминалы, управляемые вычислительной машиной.
//С терминала клиент вводит название своей станции отправления SA и станции назначения SP, ему должно выдаваться расписание поездов, обеспечивающих минимальное время поездки.
//Написать программу для получения нужной информации. Расписание (это ваш банк данных) представлено данными некоторой структуры, где перечисляется время отправления (прибытия) всех поездов.
//Разумеется, не между станциями есть прямое сообщение.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;

namespace GaGW_WPF
{
    class Edge
    {
        public int a, b, start, stop;
        public Edge(int a, int b, int start, int stop)
        {
            this.a = a;
            this.b = b;
            this.start = start;
            this.stop = stop;
        }
    }
    public partial class MainWindow : Window
    {
        int sA, sB;
        Boolean check = true;

        static bool Find(List<int> list, int x)
        {
            if (list == null) return false;
            else
            {
                foreach (var i in list)
                {
                    if (i == x) return true;
                }
            }
            return false;
        }

        static bool Compare(List<int> L1, List<int> L2)
        {
            if (L1.Count == L2.Count)
            {
                for (var i = 0; i < L1.Count; i++)
                    if (L1[i] != L2[i]) return false;
            }
            else return false;
            return true;
        }

        static void AddWay(List<int> list, List<List<int>> listWays)
        {
            int i = 0;
            bool temp = true;
            while (i < listWays.Count && temp)
            {
                if (Compare(list, listWays[i])) temp = false;
                else i++;
            }
            if (temp || i == listWays.Count)
            {
                listWays.Add(new List<int>());
                foreach (var j in list)
                {
                    listWays[listWays.Count - 1].Add(j);
                }
            }
        }

        static void Ways(List<Edge> edges, int numberEdge, List<int> list, List<List<int>> listWays)
        {
            foreach (var edge in edges)
            {
                if (!Find(list, numberEdge))
                {
                    if (edge.a == numberEdge)
                    {
                        list.Add(numberEdge);

                        if (!Find(list, edge.b)) Ways(edges, edge.b, list, listWays);
                        else AddWay(list, listWays);
                        list.Remove(numberEdge);
                    }
                    else if (edge.b == numberEdge)
                    {
                        list.Add(numberEdge);

                        if (!Find(list, edge.a)) Ways(edges, edge.a, list, listWays);
                        else AddWay(list, listWays);
                        list.Remove(numberEdge);
                    }
                }
            }
        }

        public int Print(List<int> list, int i)
        {
            return list[i];
        }

        /*
        public void Print2()
        {
            
            foreach (var i in listWays)
            {
                if ((i[0] == sA) & (i[i.Count - 1] == 10))
                {
                    Ways_AB.Add(i);
                }
            }
        }
        */

        List<Edge> edges = new List<Edge>();
        List<List<int>> Ways_AB = new List<List<int>>();
        List<List<int>> listWays = new List<List<int>>();
        public MainWindow()
        {
            edges.Add(new Edge(1, 2, 390, 450)); //  A -> B ( 06:30 07:30 )
            edges.Add(new Edge(2, 1, 790, 815)); //  B -> A ( 13:10 13:35 )
            edges.Add(new Edge(2, 3, 465, 500)); //  B -> C ( 07:45 08:20 )
            edges.Add(new Edge(2, 5, 470, 540)); //  B -> E ( 07:50 09:00 )
            edges.Add(new Edge(3, 2, 785, 810)); //  C -> B ( 13:05 13:30 )
            edges.Add(new Edge(3, 4, 520, 660)); //  C -> D ( 08:40 11:00 )
            edges.Add(new Edge(3, 8, 530, 600)); //  C -> H ( 08:50 10:00 )
            edges.Add(new Edge(4, 3, 660, 690)); //  D -> C ( 11:00 11:30 )
            edges.Add(new Edge(4, 7, 665, 705)); //  D -> G ( 11:05 11:45 )
            edges.Add(new Edge(5, 2, 770, 780)); //  E -> B ( 13:50 13:00 )
            edges.Add(new Edge(5, 6, 600, 710)); //  E -> F ( 10:00 11:50 )
            edges.Add(new Edge(6, 5, 745, 760)); //  F -> E ( 12:25 12:40 )
            edges.Add(new Edge(6, 7, 700, 720)); //  F -> G ( 11:40 12:00 )
            edges.Add(new Edge(6, 8, 610, 690)); //  F -> H ( 10:10 11:30 )
            edges.Add(new Edge(6, 9, 660, 690)); //  F -> I ( 11:00 11:30 )
            edges.Add(new Edge(7, 4, 605, 655)); //  G -> D ( 10:05 10:55 )
            edges.Add(new Edge(7, 6, 725, 740)); //  G -> F ( 12:05 12:20 )
            edges.Add(new Edge(7, 10, 730, 750)); // G -> J ( 12:10 12:30 )
            edges.Add(new Edge(8, 3, 760, 780)); //  H -> C ( 12:40 13:00 )
            edges.Add(new Edge(8, 6, 730, 750)); //  H -> F ( 12:10 12:30 )
            edges.Add(new Edge(9, 6, 720, 725)); //  I -> F ( 12:00 12:05 )
            edges.Add(new Edge(9, 10, 720, 755)); // I -> J ( 12:00 12:35 )
            edges.Add(new Edge(10, 7, 540, 600)); // J -> G ( 09:00 10:00 )
            edges.Add(new Edge(10, 9, 660, 675)); // J -> I ( 11:00 11:15 )
            
            InitializeComponent();
            TextB.Visibility = Visibility.Hidden;



        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 1. Выберите станцию прибытия";
                sA = 1;
                check = false;
            }
            else if ((check == false) && (sA != 1))
            {
                Label1.Content = "Место прибытия -> станция 1. Нажмите кнопку";
                sB = 1;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 2. Выберите станцию прибытия";
                sA = 2;
                check = false;
            }
            else if ((check == false) && (sA != 2))
            {
                Label1.Content = "Место прибытия -> станция 2. Нажмите кнопку";
                sB = 2;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 3. Выберите станцию прибытия";
                sA = 3;
                check = false;
            }
            else if ((check == false) && (sA != 3))
            {
                Label1.Content = "Место прибытия -> станция 3. Нажмите кнопку";
                sB = 3;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 4. Выберите станцию прибытия";
                sA = 4;
                check = false;
            }
            else if ((check == false) && (sA != 4))
            {
                Label1.Content = "Место прибытия -> станция 4. Нажмите кнопку";
                sB = 4;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_5(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 5. Выберите станцию прибытия";
                sA = 5;
                check = false;
            }
            else if ((check == false) && (sA != 5))
            {
                Label1.Content = "Место прибытия -> станция 5. Нажмите кнопку";
                sB = 5;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_6(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 6. Выберите станцию прибытия";
                sA = 6;
                check = false;
            }
            else if ((check == false) && (sA != 6))
            {
                Label1.Content = "Место прибытия -> станция 6. Нажмите кнопку";
                sB = 6;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_7(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 7. Выберите станцию прибытия";
                sA = 7;
                check = false;
            }
            else if ((check == false) && (sA != 7))
            {
                Label1.Content = "Место прибытия -> станция 7. Нажмите кнопку";
                sB = 7;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_8(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 8. Выберите станцию прибытия";
                sA = 8;
                check = false;
            }
            else if ((check == false) && (sA != 8))
            {
                Label1.Content = "Место прибытия -> станция 8. Нажмите кнопку";
                sB = 8;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_9(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 9. Выберите станцию прибытия";
                sA = 9;
                check = false;
            }
            else if ((check == false) && (sA != 9))
            {
                Label1.Content = "Место прибытия -> станция 9. Нажмите кнопку";
                sB = 9;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_10(object sender, RoutedEventArgs e)
        {
            if (check == true)
            {
                Label1.Content = "Место отправки -> станция 10. Выберите станцию прибытия";
                sA = 10;
                check = false;
            }
            else if ((check == false) && (sA != 10))
            {
                Label1.Content = "Место прибытия -> станция 10. Нажмите кнопку";
                sB = 10;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_najmi(object sender, RoutedEventArgs e)
        {
            Ways(edges, sA, new List<int>(), listWays); //граф, откуда начать, лист интов, лист путей 
            Label1.Visibility = Visibility.Hidden;
            TextB.Text = "Вы выбрали путь из станции " + sA +" в станцию " + sB + "\n";
            foreach (var i in listWays)
            {
                if ((i[0] == sA) & (i[i.Count - 1] == sB))
                {
                    for (var j = 0; j < i.Count; j++)
                    {
                        if (j != i.Count - 1) TextB.Text += Print(i, j) + "-";
                        else TextB.Text += Print(i, j);
                    }
                    TextB.Text += "\n";
                }
            }
            TextB.Visibility = Visibility.Visible;
        }
    }
}

/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GaGW_WPF
{
    public partial class MainWindow : Window
    {
         int[,] station = new int[,] {{0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // 1 поезд
                                     {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},  // 2 поезд
                                     {0, 1, 0, 1, 0, 0, 0, 1, 0, 0},  // 3
                                     {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},  // 4
                                     {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},  // 5
                                     {0, 0, 0, 0, 1, 0, 1, 1, 1, 0},  // 6
                                     {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},  // 7
                                     {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},  // 8
                                     {0, 0, 0, 0, 0, 1, 0, 0, 0, 1},  // 9
                                     {0, 0, 0, 0, 0, 0, 1, 0, 1, 0}}; // 10
        int[,] a = new int[20, 20];
        int pathn;

        public struct train
        {
            public string num;
            public int start;
            public int stop;
        }
        train[] trains = new train[100];


        public int Poisk(int num, int prev, int dest, int step) // рекурсивная функция нахождения всех возможных путей из одного пункта в другой
        {
            if (num != dest) //если пункт а не равен пункту б
            {
                for (int i = 0; i < 10; i++) // с 1 по 10
                {
                    if (station[num, i] == 1)
                    {
                        if ((trains[prev + 10 * i].stop <= trains[num + 10 * i].start) && (num != prev))
                        {
                            a[pathn, step] = Poisk(i, num, dest, step + 1);
                            Label2.Content = "aye";
                            return num + 10 * i;
                        }
                        else break;
                    }
                    else
                    {
                        Label1.Content = "break";
                    }
                }
            }
            else
            {
                pathn = pathn + 1;

            }
            Label1.Content = "da";
            return 0;
        }

        public void min()
        {
            int x, min_ind, min;
            min_ind = 0;
            x = 0;
            min = 999999999;
            for (int i = 1; i < 10; i++)
            {

                for (int j = 1; j < 10; j++) if (a[i,j] != 0) x = j;
                if (min > (trains[a[i, 1]].stop - trains[a[i, x]].start))
                {
                    min_ind = i;
                    min = trains[a[i, 1]].stop - trains[a[i, x]].start;
                }
            }
            for (int i = 1; i < 10; i++)
            {
                if (a[min_ind, i] != 0)  Label2.Content = trains[a[min_ind, i]].num + " -> ";
            }
            Label1.Content = "Time in path: " + min;
        }

        int punktA, punktB, shet = 1;
        public MainWindow()
        {
            trains[2].num  = "2" ; trains[2].start =  790; trains[2].stop =  815; // B -> A  13:10 13:35    
            trains[11].num = "1" ; trains[11].start = 390; trains[11].stop = 450; // A -> B  06:30 07:30
            trains[13].num = "4" ; trains[13].start = 785; trains[13].stop = 810; // C -> B  13:05 13:30
            trains[15].num = "6" ; trains[15].start = 770; trains[15].stop = 780; // E -> B  12:50 13:00
            trains[22].num = "3" ; trains[22].start = 465; trains[22].stop = 500; // B -> C  07:45 08:20
            trains[24].num = "8" ; trains[24].start = 660; trains[24].stop = 690; // D -> C  11:00 11:30
            trains[28].num = "10"; trains[28].start = 760; trains[28].stop = 780; // H -> C  12:40 13:00
            trains[33].num = "7" ; trains[33].start = 520; trains[33].stop = 660; // C -> D  08:40 11:00
            trains[37].num = "14"; trains[37].start = 605; trains[37].stop = 655; // G -> D  10:05 10:55
            trains[42].num = "5" ; trains[42].start = 470; trains[42].stop = 540; // B -> E  07:50 09:00
            trains[46].num = "12"; trains[46].start = 745; trains[46].stop = 760; // F -> E  12:25 12:40
            trains[55].num = "11"; trains[55].start = 600; trains[55].stop = 710; // E -> F  10:00 11:50
            trains[57].num = "16"; trains[57].start = 725; trains[57].stop = 740; // G -> F  12:05 12:20
            trains[58].num = "18"; trains[58].start = 610; trains[58].stop = 690; // H -> F  10:10 11:30
            trains[64].num = "13"; trains[64].start = 665; trains[64].stop = 705; // D -> G  11:05 11:45
            trains[66].num = "15"; trains[66].start = 700; trains[66].stop = 720; // F -> G  11:40 12:00
            trains[70].num = "24"; trains[70].start = 540; trains[70].stop = 600; // K -> G  09:00 10:00
            trains[73].num = "9" ; trains[73].start = 530; trains[73].stop = 600; // C -> H  08:50 10:00
            trains[76].num = "17"; trains[76].start = 730; trains[76].stop = 750; // F -> H  12:10 12:30
            trains[86].num = "19"; trains[86].start = 660; trains[86].stop = 690; // F -> I  11:00 11:30
            trains[90].num = "22"; trains[90].start = 660; trains[90].stop = 675; // K -> I  11:00 11:15
            trains[97].num = "23"; trains[97].start = 730; trains[97].stop = 750; // G -> K  12:10 12:30
            trains[99].num = "21"; trains[99].start = 720; trains[99].stop = 755; // I -> K  12:00 12:35

            InitializeComponent();
            Label1.Content = "Выберите станцию отбытия";
        }


        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция A. Выберите станцию прибытия";
                punktA = 0;
                shet++;
            }
            else if ((shet == 2) && (punktA != 1))
            {
                punktB = 1;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция B. Выберите станцию прибытия";
                punktA = 2;
                shet++;
            }
            else if ((shet == 2) && (punktA != 2))
            {
                punktB = 2;
                
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция C. Выберите станцию прибытия";
                punktA = 3;
                shet++;

            }
            else if ((shet == 2) && (punktA != 3))
            {
                punktB = 3;
                a[1, 1] = Poisk(punktA, 0, punktB, 1);
                min();
                Label1.Content = shet;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция D. Выберите станцию прибытия";
                punktA = 4;
                shet++;
            }
            else if ((shet == 2) && (punktA != 4))
            {
                punktB = 4;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_5(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция E. Выберите станцию прибытия";
                punktA = 5;
                shet++;
            }
            else if ((shet == 2) && (punktA != 5))
            {
                punktB = 5;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_6(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция F. Выберите станцию прибытия";
                punktA = 6;
                shet++;
            }
            else if ((shet == 2) && (punktA != 6))
            {
                punktB = 6;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_7(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция G. Выберите станцию прибытия";
                punktA = 7;
                shet++;
            }
            else if ((shet == 2) && (punktA != 7))
            {
                punktB = 7;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_8(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция H. Выберите станцию прибытия";
                punktA = 8;
                shet++;
            }
            else if ((shet == 2) && (punktA != 8))
            {
                punktB = 7;
                a[1, 1] = Poisk(punktA, 0, punktB, 1);
                min();
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_9(object sender, RoutedEventArgs e) //пункт 9
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция I. Выберите станцию прибытия";
                punktA = 8;
                shet++;
            }
            else if ((shet == 2) && (punktA != 8))
            {
                punktB = 8;
                a[1, 1] = Poisk(punktA, 0, punktB, 1);
                min();
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_10(object sender, RoutedEventArgs e)
        {
            if (shet == 1)
            {
                Label1.Content = "Место отправки -> станция J. Выберите станцию прибытия";
                punktA = 10;
                shet++;
            }
            else if ((shet == 2) && (punktA != 10))
            {
                punktB = 10;
            }
            else
            {
                Label1.Content = "Станция прибытия не может быть станцией отбытия. Повторите попытку";
            }
        }

        private void Button_Click_najmi(object sender, RoutedEventArgs e)
        {
            Button_najmi.Visibility = Visibility.Hidden;
            Label1.Visibility = Visibility.Hidden;
            Label2.Content = "Вы выбрали путь из пункта " + punktA + " в пункт " + punktB;

        }
    }
}
*/
#pragma once

namespace Project1 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO::Ports;
    using namespace System::Windows::Forms::DataVisualization::Charting;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Label^ label1;
        SerialPort^ serialPort;
        Chart^ chart1;  // Grafik kontrolü
        
        array<double>^ basincData;
        array<double>^ sicaklikData;
        array<double>^ sayacData;
        array<double>^ irtifaData;
        array<double>^ roketGPSIrtifaData;
        array<double>^ roketBoylamData;
        array<double>^ roketEnlemData;
        array<double>^ gorevYukuGPSIrtifaData;
        array<double>^ gorevYukuEnlemData;
        array<double>^ gorevYukuBoylamData;
        array<double>^ jireskopXData;
        array<double>^ jireskopYData;
        array<double>^ jireskopZData;
        array<double>^ ivmeXData;
        array<double>^ ivmeYData;
        array<double>^ ivmeZData;
        array<double>^ durumData;
        array<double>^ crcData;
        array<double>^ pilGerilimData;
        array<double>^ hizData;
        array<double>^ tarihData;
        array<double>^ saatData;
        array<double>^ payloadSicaklikData;
        array<double>^ payloadIrtifaData;
        array<double>^ nemData;
        array<double>^ aciXData;
        array<double>^ aciYData;
        array<double>^ aciZData;


        int dataIndex = 0;  // Veri indeksini takip eder
        const int dataSize = 50;  // Veri dizilerinin boyutunu artırdık

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->Location = System::Drawing::Point(133, 110);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(624, 465);
            this->label1->TabIndex = 1;
            this->label1->Text = L"Veri burada görünecek";
            this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
            // 
            // chart1
            // 
            this->chart1->Location = System::Drawing::Point(823, 279);
            this->chart1->Name = L"chart1";
            this->chart1->Size = System::Drawing::Size(547, 364);
            this->chart1->TabIndex = 2;
            this->chart1->Text = L"chart1";
            this->chart1->Click += gcnew System::EventHandler(this, &MyForm::chart1_Click);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1456, 688);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->chart1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion

        // Form yüklenirken seri portu başlat
        void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
            serialPort = gcnew SerialPort("COM3", 9600);  // COM3 olarak güncellendi
            serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(this, &MyForm::SerialPort_DataReceived);

            // Grafik verilerini başlat
           
            basincData = gcnew array<double>(dataSize);
            sicaklikData = gcnew array<double>(dataSize);
            sayacData = gcnew array<double>(dataSize);
            irtifaData = gcnew array<double>(dataSize);
            roketGPSIrtifaData = gcnew array <double>(dataSize);
            roketBoylamData = gcnew array <double>(dataSize);
            roketEnlemData = gcnew array <double>(dataSize);
            gorevYukuGPSIrtifaData = gcnew array <double>(dataSize);
            gorevYukuEnlemData = gcnew array <double>(dataSize);
            gorevYukuBoylamData = gcnew array <double>(dataSize);
            jireskopXData = gcnew array <double>(dataSize);
            jireskopYData = gcnew array <double>(dataSize);
            jireskopZData = gcnew array <double>(dataSize);
            ivmeXData = gcnew array<double>(dataSize);
            ivmeYData = gcnew array<double>(dataSize);
            ivmeZData = gcnew array<double>(dataSize);
            durumData = gcnew array<double>(dataSize);
            crcData = gcnew array<double>(dataSize);
            pilGerilimData = gcnew array<double>(dataSize);
            hizData = gcnew array<double>(dataSize);
            tarihData = gcnew array<double>(dataSize);
            saatData = gcnew array<double>(dataSize);
            payloadSicaklikData = gcnew array<double>(dataSize);
            payloadIrtifaData = gcnew array<double>(dataSize);
            nemData = gcnew array<double>(dataSize);
            aciXData = gcnew array<double>(dataSize);
            aciYData = gcnew array<double>(dataSize);
            aciZData = gcnew array<double>(dataSize);

            try
            {
                serialPort->Open();  // Seri portu aç
                label1->Text = L"Seri port açıldı.";
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Seri port açılamadı: " + ex->Message);
            }
        }

        // Seri port üzerinden veri alındığında tetiklenen olay
        void SerialPort_DataReceived(System::Object^ sender, SerialDataReceivedEventArgs^ e)
        {
            String^ data = serialPort->ReadLine();  // Seri porttan gelen veriyi oku
            this->Invoke(gcnew Action<String^>(this, &MyForm::UpdateData), data);  // Veriyi güncelle
        }

        // Verileri güncelle ve grafikte göster
        void UpdateData(String^ data)
        {
            array<String^>^ values = data->Split(',');

            if (values->Length == 28)
            {
                try
                {
                    
                    basincData[dataIndex] = Double::Parse(values[0]);
                    sicaklikData[dataIndex] = Double::Parse(values[1]);
                    sayacData[dataIndex] = Double::Parse(values[2]);
                    irtifaData[dataIndex] = Double::Parse(values[3]);
                    roketGPSIrtifaData[dataIndex] = Double::Parse(values[4]);
                    roketBoylamData[dataIndex] = Double::Parse(values[5]);
                    roketEnlemData[dataIndex] = Double::Parse(values[6]);
                    gorevYukuGPSIrtifaData[dataIndex] = Double::Parse(values[7]);
                    gorevYukuEnlemData[dataIndex] = Double::Parse(values[8]);
                    gorevYukuBoylamData[dataIndex] = Double::Parse(values[9]);
                    jireskopXData[dataIndex] = Double::Parse(values[10]);
                    jireskopYData[dataIndex] = Double::Parse(values[11]);
                    jireskopZData[dataIndex] = Double::Parse(values[12]);
                    ivmeXData[dataIndex] = Double::Parse(values[13]);
                    ivmeYData[dataIndex] = Double::Parse(values[14]);
                    ivmeZData[dataIndex] = Double::Parse(values[15]);
                    durumData[dataIndex] = Double::Parse(values[16]);
                    crcData[dataIndex] = Double::Parse(values[17]);
                    pilGerilimData[dataIndex] = Double::Parse(values[18]);
                    hizData[dataIndex] = Double::Parse(values[19]);
                    payloadSicaklikData[dataIndex] = Double::Parse(values[22]);
                    payloadIrtifaData[dataIndex] = Double::Parse(values[23]);
                    nemData[dataIndex] = Double::Parse(values[24]);
                    aciXData[dataIndex] = Double::Parse(values[25]);
                    aciYData[dataIndex] = Double::Parse(values[26]);
                    aciZData[dataIndex] = Double::Parse(values[27]);

                    // Veri indeksini arttır
                    dataIndex = (dataIndex + 1) % dataSize;

                    label1->Text =
                        "Basınç: " + values[0] + Environment::NewLine +
                        "Sıcaklık: " + values[1] + Environment::NewLine +
                        "Sayac: " + values[2] + Environment::NewLine +
                        "İrtifa: " + values[3] + Environment::NewLine +
                        "RoketGPSIrtifa: " + values[4] + Environment::NewLine +
                        "RoketBoylam: " + values[5] + Environment::NewLine +
                        "RoketEnlem: " + values[6] + Environment::NewLine +
                        "gorevYukuGPSIrtifa: " + values[7] + Environment::NewLine +
                        "gorevYukuEnlem: " + values[8] + Environment::NewLine +
                        "gorevYukuBoylam: " + values[9] + Environment::NewLine +
                        "jireskopX: " + values[10] + Environment::NewLine +
                        "jireskopY: " + values[11] + Environment::NewLine +
                        "jireskopZ: " + values[12] + Environment::NewLine +
                        "İvmeX: " + values[13] + Environment::NewLine +
                        "ivmeY: " + values[14] + Environment::NewLine +
                        "ivmeZ: " + values[15] + Environment::NewLine +
                        "durum: " + values[16] + Environment::NewLine +
                        "crc: " + values[17] + Environment::NewLine +
                        "pilGerilim: " + values[18] + Environment::NewLine +
                        "hiz: " + values[19] + Environment::NewLine +
                        "tarih: " + values[20] + Environment::NewLine +
                        "saat: " + values[21] + Environment::NewLine +
                        "payloadSicaklik: " + values[22] + Environment::NewLine +
                        "payloadIrtifa: " + values[23] + Environment::NewLine +
                        "nem: " + values[24] + Environment::NewLine +
                        "aciX: " + values[25] + Environment::NewLine +
                        "aciY: " + values[26] + Environment::NewLine +
                        "aciZ: " + values[27] + Environment::NewLine;


                    // Grafikteki verileri güncelle
                    UpdateChart();
                }
                catch (FormatException^)
                {
                    // Hata mesajı göster, giriş formatı hatalıysa
                    MessageBox::Show("Veri formatı hatalı!");
                }
            }
        }

        // Grafiği güncelle
        void UpdateChart()
        {
            // Grafik alanını ve serileri oluştur
            if (chart1->ChartAreas->Count == 0)
            {
                // İlk defa ChartArea ekleniyor
                ChartArea^ chartArea = gcnew ChartArea();
                chart1->ChartAreas->Add(chartArea);
            }

            // Grafik serilerini oluştur
            chart1->Series->Clear();

            // Serileri oluştur
            Series^ ivmeSeries = gcnew Series("İvme");
            ivmeSeries->Points->DataBindY(ivmeXData);
            ivmeSeries->ChartType = SeriesChartType::Line; // Çizgi grafiği
            ivmeSeries->BorderWidth = 3;
            ivmeSeries->Color = Color::Blue; // Mavi renk

            Series^ basincSeries = gcnew Series("Basınç");
            basincSeries->Points->DataBindY(basincData);
            basincSeries->ChartType = SeriesChartType::Line; // Çizgi grafiği
            basincSeries->BorderWidth = 3;
            basincSeries->Color = Color::Green; // Yeşil renk

            Series^ sicaklikSeries = gcnew Series("Sıcaklık");
            sicaklikSeries->Points->DataBindY(sicaklikData);
            sicaklikSeries->ChartType = SeriesChartType::Line; // Çizgi grafiği
            sicaklikSeries->BorderWidth = 3;
            sicaklikSeries->Color = Color::Red; // Kırmızı renk

            // Grafikteki serileri ekle
            chart1->Series->Add(ivmeSeries);
            chart1->Series->Add(basincSeries);
            chart1->Series->Add(sicaklikSeries);
        }

        // Form kapandığında seri portu kapat
        void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
            if (serialPort->IsOpen)
            {
                serialPort->Close();  // Seri portu kapat
            }
        }

    private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}
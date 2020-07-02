
#pragma once

namespace TakionBridge { namespace Gateway {

	class MainDialog : public TakionSettingTopDialog {
	public:
		MainDialog();
		void Top();
		void Corner();
		virtual void Apply();
	protected:
		virtual BOOL OnInitDialog();
		virtual void FinishDialog(int result);
	};

} }

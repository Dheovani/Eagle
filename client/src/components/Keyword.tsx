import { useState, useEffect, useCallback } from "react";
import { GiBroom } from "react-icons/gi";
import { GetMethod } from "@/utils/RestMethods";
import Tooltip from "@/components/Tooltip";
import History, { KEYWORD } from "@/components/History";
import Input from "@/components/Input";

export interface Keyword {
	keyword: string;
	id?: number;
}

const KeywordInput = (props: any): JSX.Element => {
	const {
		defaultValue,
		updateDefaultValue
	} = props;

	const [selected, setSelected] = useState(false);
	const [keyword, setKeyword] = useState<Keyword[]>([]);

	const updateHistory = (): void => {
		GetMethod("http://localhost:8080/api/v1/Keyword", (status: number, response: any) => {
			if (status === 200) setKeyword(response.results);
		});
	};

	useEffect(() => {
		updateHistory();
	}, [selected]);

	const renderHistory = (): JSX.Element => {
		if (!keyword?.length) return <div></div>;

		return (
			<History
				items={keyword}
				endpoint={KEYWORD}
				updateDefaultValue={updateDefaultValue}
			/>
		);
	};

	const onSelect = useCallback(() => {
		setTimeout(() => setSelected(!selected), 100)
	}, []);

	const info = "Este campo contém as palavras que devem ser buscadas.";

	return (
		<>
			<h2>
				Pesquisa
				{<Tooltip info={info} />}
			</h2>

			<div className="input-content">
				<Input
					id="keyword"
					placeholder="Digite aqui as palavras-chave"
					defaultValue={defaultValue}
					selected={selected}
					setSelected={setSelected}
					onChange={(e) => {
						updateDefaultValue({
							path: e.target.value
						});
					}}
				/>

				<button className="input-buttons" onClick={() => updateDefaultValue({ keyword: "" })}>
					<GiBroom />
				</button>
			</div>

			{selected && renderHistory()}
		</>
	);
};

export default KeywordInput;